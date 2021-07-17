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
Renderer::Renderer()
{

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

  // デバイスにアクセスするためのインターフェースを作成
  auto dxgiFactory = CreateDXGIFactory();
  // D3Dデバイスの作成
  if (!CreateD3DDevice(dxgiFactory))
  {
    // D3Dデバイスの作成に失敗
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
      IID_PPV_ARGS(&_d3d_device)
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

  return _d3d_device != nullptr;
}
