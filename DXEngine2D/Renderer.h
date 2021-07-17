/**
 * @file    Renderer.h
 * @author  tatsuki kanno
 * @date    2021/07/03
 * @brief   レンダラークラス
 * @details
 */
#pragma once

#include "stdafx.h"
#include <wrl.h>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <dxgi1_3.h>
#include <dxgi1_4.h>
#include "Object.h"


class Renderer
{
public:
    Renderer();
    ~Renderer();

    virtual void Initialize();
    virtual void Update();
    virtual void Finalize();

    void Register(class RenderComponent* object);
    void Unregister(class RenderComponent* object);

    // レンダリング開始
    void BeginRender();

    // レンダリング終了
    void EndRender();

    // D3Dデバイスを取得
    ID3D12Device5* GetD3DDevice();

    // バックバッファ番号を取得
    UINT GetBackBufferIndex() const;

    // コマンドキューを取得
    ID3D12CommandQueue* GetCommandQueue() const;

    // コマンドリストを取得
    ID3D12GraphicsCommandList4* GetCommandList() const;

    // CBR_SRVのディスクリプタのサイズを取得
    UINT GetCbrSrvDescriptorSize() const;

    // サンプラのディスクリプタヒープサイズを取得
    UINT GetSamplerDescriptorSize() const;

    // レンダリングコンテキストを取得
    //RenderContext& GetRenderContext();



private:
    //! DXGI(DirectX Graphics Infrastructure)Factoryを作成する
    IDXGIFactory4* CreateDXGIFactory();

    //! D3Dデバイスを作成する
    bool CreateD3DDevice(IDXGIFactory4* dxgiFactory);

    //! コマンドキューの作成
    bool CreateCommandQueue();

    //! スワップチェインの作成
    //! @param hwnd Windowハンドル
    //! @param frameBufferWidth フレームバッファの幅
    //! @param frameBufferHeight フレームバッファの高さ
    //! @param dxgiFactory DirectX グラフィックス インフラストラクチャー
    //! @return true 作成に成功
    bool CreateSwapChain(
      HWND hwnd,
      UINT frameBufferWidth,
      UINT frameBufferHeight,
      IDXGIFactory4* dxgiFactory
    );

public:
  enum {FRAME_BUFFER_COUNT = 2 }; // フレームバッファの数
private:
    //! GPUベンダー定義
    enum GPU_Vender {
        GPU_VenderNvidia,   //! NVIDIA
        GPU_VenderAMD,      //! Intel
        GPU_VenderIntel,    //! AMD
        Num_GPUVender,
    };

    std::vector<class RenderComponent*> _renderList;
    static Renderer* kInstance;

    ID3D12Device5* _d3d_device          = nullptr;  //! D3Dデバイス
    ID3D12CommandQueue* _commandQueue   = nullptr;  //! コマンドキュー
    IDXGISwapChain3* _swapChain         = nullptr;  //! スワップチェイン
    int _currentBackBufferIndex         = 0;        //! 現在のバックバッファの番号


};
