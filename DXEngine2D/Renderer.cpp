/**
 * @file    Renderer.cpp
 * @author  tatsuki kanno
 * @date    2021/07/03
 * @brief   レンダラークラス
 * @details
 */

#include "Renderer.h"
#include "RenderComponent.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

using namespace Microsoft::WRL;

Renderer* Renderer::kInstance = nullptr;

/**
 * @brief   コンストラクタ
 */
Renderer::Renderer(InitData& data)
  : _d3dDevice              (nullptr)
  , _commandQueue           (nullptr)
  , _swapChain              (nullptr)
  , _currentBackBufferIndex (0)
  , _rtvHeap                (nullptr)
  , _dsvHeap                (nullptr)
  , _rtvDescriptorSize      (0)
  , _dsvDescriptorSize      (0)
{
  _initData = data;
}

/**
 * @brief   デストラクタ
 */
Renderer::~Renderer()
{

}

/**
 * @brief       初期化関数
 * @details     初期化処理
 */
void Renderer::Initialize()
{
  if(kInstance == nullptr)
    kInstance = this;

  //! デバイスにアクセスするためのインターフェースを作成
  auto dxgiFactory = CreateDXGIFactory();
  //! D3Dデバイスの作成
  if (!CreateD3DDevice(dxgiFactory))
  {
    return;
  }
  _initData.dxgiFactory = dxgiFactory;

  //! コマンドキューの作成
  if (!CreateCommandQueue()) {
    return;
  }

  // スワップチェインの作成
  if (!CreateSwapChain())
  {
    return;
  }

  // 初期化が終わったのでDXGIを破棄
  dxgiFactory->Release();

}

/**
 * @brief   更新関数
 * @details 更新処理
 */
void Renderer::Update()
{
  for (auto render : _renderList)
  {
    render->Update();
  }
}

/**
 * @brief   終了処理関数
 * @details 終了時の終了処理
 */
void Renderer::Finalize()
{

}

/**
 * @brief   オブジェクトを登録する
 * @details 
 */
void Renderer::Register(RenderComponent* renderComp)
{
  _renderList.push_back(renderComp);
}

/**
 * @brief       オブジェクトを解除する
 * @details     
 */
void Renderer::Unregister(RenderComponent* renderComp)
{
  auto iter = std::find(_renderList.begin(), _renderList.end(), renderComp);
  if (iter != _renderList.end())
  {
    _renderList.erase(iter);
  }
}



///=============================================================================
///@brief   DXGI(DirectX Graphics Infrastructure)Factoryを作成する
///@details 
///=============================================================================
IDXGIFactory4* Renderer::CreateDXGIFactory()
{
  UINT dxgiFactoryFlags = 0;

#ifdef _DEBUG
  // デバッグレイヤーを有効にする
  ComPtr<ID3D12Debug> debugController = nullptr;
  auto result = D3D12GetDebugInterface(
    IID_PPV_ARGS(debugController.ReleaseAndGetAddressOf())
  );
  if (SUCCEEDED(result))
  {
    debugController->EnableDebugLayer();
      // Enable additional debug layers.
      dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
  }
#endif

  IDXGIFactory4* factory;
  CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory));

  return factory;
}

/**
 * @brief       D3Dデバイスを作成する
 * @details
 */
bool Renderer::CreateD3DDevice(IDXGIFactory4* dxgiFactory)
{
  D3D_FEATURE_LEVEL featureLevels[] = 
  {
    D3D_FEATURE_LEVEL_12_1, //<! Direct3D 12.1の機能を使う
    D3D_FEATURE_LEVEL_12_0, //<! Direct3D 12.0の機能を使う
  };

  IDXGIAdapter* adapterTmp = nullptr;
  IDXGIAdapter* adapterVender[Num_GPUVender] = { nullptr }; /// 各ベンダーのアダプター
  IDXGIAdapter* adapterMaxVideoMemory = nullptr;            /// 最大ビデオメモリのアダプタ
  IDXGIAdapter* useAdapter = nullptr;                       /// 最終的に使用するアダプタ
  SIZE_T videoMemorySize = 0;

  for (int i = 0; dxgiFactory->EnumAdapters(i, &adapterTmp) != DXGI_ERROR_NOT_FOUND; i++)
  {
    DXGI_ADAPTER_DESC desc;
    adapterTmp->GetDesc(&desc);

    if (desc.DedicatedVideoMemory > videoMemorySize) {
      // ビデオメモリの方が多いので、こちらを使う
      if (adapterMaxVideoMemory != nullptr)
      {
        adapterMaxVideoMemory->Release();
      }
      adapterMaxVideoMemory = adapterTmp;
      adapterMaxVideoMemory->AddRef();
      videoMemorySize = desc.DedicatedVideoMemory;
    }

    if (wcsstr(desc.Description, L"NVIDIA") != nullptr) {
      // NVIDIA製
      if (adapterVender[GPU_VenderNvidia]) {
        adapterVender[GPU_VenderNvidia]->Release();
      }
      adapterVender[GPU_VenderNvidia] = adapterTmp;
      adapterVender[GPU_VenderNvidia]->AddRef();
    }
    else if (wcsstr(desc.Description, L"AMD") != nullptr) {
      // AMD製
      if (adapterVender[GPU_VenderAMD]) {
        adapterVender[GPU_VenderAMD]->Release();
      }
      adapterVender[GPU_VenderAMD] = adapterTmp;
      adapterVender[GPU_VenderAMD]->AddRef();
    }
    else if (wcsstr(desc.Description, L"Intel") != nullptr) {
      // Intel製
      if (adapterVender[GPU_VenderIntel]) {
        adapterVender[GPU_VenderIntel]->Release();
      }
      adapterVender[GPU_VenderIntel] = adapterTmp;
      adapterVender[GPU_VenderIntel]->AddRef();
    }
    adapterTmp->Release();
  }

  // 使用するアダプターを決める
  if (adapterVender[GPU_VenderNvidia] != nullptr) {
    // NVIDIA製が最優先
    useAdapter = adapterVender[GPU_VenderNvidia];
  }
  else if (adapterVender[GPU_VenderAMD] != nullptr) {
    // 次はAMDが優先
    useAdapter = adapterVender[GPU_VenderAMD];
  }
  else {
    // NVIDIAとAMDのGPUがなければビデオメモリが一番多いやつを使う
    useAdapter = adapterMaxVideoMemory;
  }

  for (auto featureLevel : featureLevels) {
    auto hr = D3D12CreateDevice(
      useAdapter,
      featureLevel,
      IID_PPV_ARGS(&_d3dDevice)
    );
    if (SUCCEEDED(hr)) {
      // D3Dデバイスの作成
      break;
    }
  }

  for (auto& adapter : adapterVender) {
    if (adapter) {
      adapter->Release();
    }
  }

  if (adapterMaxVideoMemory) {
    adapterMaxVideoMemory->Release();
  }

  return _d3dDevice != nullptr;
}

/**
 * @brief       コマンドキューの作成
 * @details     GPUに対して命令を発行するためのキュー
 */
bool Renderer::CreateCommandQueue() {
  D3D12_COMMAND_QUEUE_DESC queueDesc = {};
  queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
  queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

  auto hr = _d3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&_commandQueue));
  if (FAILED(hr)) {
    //! コマンドキューの作成
    return false;
  }
  return true;
}

/**
 * @brief       スワップチェインの作成
 * @details     バックバッファを管理して、表画面を切り替える機構
 */
bool Renderer::CreateSwapChain() {
  return CreateSwapChain(
    _initData.hwnd,
    _initData.frameBufferWidth,
    _initData.frameBufferHeight,
    _initData.dxgiFactory
  );
};

/**
 * @brief       スワップチェインの作成
 * @details     バックバッファを管理して、表画面を切り替える機構
 */
bool Renderer::CreateSwapChain(
  HWND hwnd,
  UINT frameBufferWidth,
  UINT frameBufferHeight,
  IDXGIFactory4* dxgiFactory
)
{
  DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
  swapChainDesc.BufferCount       = FRAME_BUFFER_COUNT;
  swapChainDesc.Width             = frameBufferWidth;
  swapChainDesc.Height            = frameBufferHeight;
  swapChainDesc.Format            = DXGI_FORMAT_R8G8B8A8_UNORM;
  swapChainDesc.BufferUsage       = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  swapChainDesc.SwapEffect        = DXGI_SWAP_EFFECT_FLIP_DISCARD;
  swapChainDesc.SampleDesc.Count  = 1;

  IDXGISwapChain1* swapChain;
  auto result = dxgiFactory->CreateSwapChainForHwnd(
    _commandQueue,
    hwnd,
    &swapChainDesc,
    nullptr,
    nullptr,
    &swapChain
  );

  // IDXGISwapChain3のインターフェースを取得
  swapChain->QueryInterface(IID_PPV_ARGS(&_swapChain));
  swapChain->Release();
  // IDXGISwapChain3のインターフェースを取得
  _currentBackBufferIndex = _swapChain->GetCurrentBackBufferIndex();
  return true;
}

/**
 * @brief     フレームバッファ用のディスクリプタヒープを作成
 * @details   
 */
bool Renderer::CreateDescriptorHeapForFrameBuffer()
{
  //! RTV用のディスクリプタヒープ
  D3D12_DESCRIPTOR_HEAP_DESC desc = {};
  desc.NumDescriptors = FRAME_BUFFER_COUNT;
  desc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
  desc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

  //! RTV用のディスクリプタヒープの作成
  auto hr = _d3dDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&_dsvHeap));
  if (FAILED(hr)) {
    return false;
  }

  //! ディスクリプタのサイズを取得
  _dsvDescriptorSize = _d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

  //! DSV用のディスクリプタヒープを作成
  desc.NumDescriptors = 1;
  desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
  hr = _d3dDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&_dsvHeap));
  if (FAILED(hr)) {
    return false;
  }

  //! ディスクリプタのサイズ取得
  _dsvDescriptorSize = _d3dDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&_dsvHeap));


  return true;
}



