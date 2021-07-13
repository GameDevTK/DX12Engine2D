/**
 * @file    Renderer.cpp
 * @author  tatsuki kanno
 * @date    2021/07/03
 * @brief   レンダラークラス
 * @details
 */

#include "Renderer.h"
#include "RenderComponent.h"

Renderer* Renderer::mInstance = nullptr;

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
    if(mInstance == nullptr)
        mInstance = this;

    // デバイスにアクセスするためのインターフェースを作成
    auto dxgiFactory = CreateDXGIFactory();
    // D3Dデバイスの作成
    //if (!CreateD3DDevice(dxgiFactory))
    //{
    //    // D3Dデバイスの作成に失敗
    //}


    // 初期化が終わったのでDXGIを破棄
    dxgiFactory->Release();

}

/**
 * @brief       更新関数
 * @details     更新処理
 */
void Renderer::Update()
{
    for (auto render : renderList)
    {
        render->Update();
    }
}

/**
 * @brief       終了処理関数
 * @details     終了時の終了処理
 */
void Renderer::Finalize()
{

}

/**
 * @brief       オブジェクトを登録する
 * @details     
 */
void Renderer::Register(RenderComponent* renderComp)
{
    renderList.push_back(renderComp);
}

/**
 * @brief       オブジェクトを解除する
 * @details     
 */
void Renderer::Unregister(RenderComponent* renderComp)
{
    auto iter = std::find(renderList.begin(), renderList.end(), renderComp);
    if (iter != renderList.end())
    {
        renderList.erase(iter);
    }
}



/**
 * @brief       DXGI(DirectX Graphics Infrastructure)を解除する
 * @details
 */
IDXGIFactory4* Renderer::CreateDXGIFactory()
{
    UINT dxgiFactoryFlags = 0;
#ifdef _DEBUG
    // デバッグコントローラ
    // デバッグレイヤーがあるDXGIを作成する
    ID3D12Debug* debugController;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
    {
        debugController->EnableDebugLayer();

        // Enable additional debug layers.
        dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
        debugController->Release();
    }
#endif
    IDXGIFactory4* factory;
    CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory));

    return factory;
}
