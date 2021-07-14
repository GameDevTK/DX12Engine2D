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
    UINT GetSamplerDescriptorSizze() const;

    // レンダリングコンテキストを取得
    //RenderContext& GetRenderContext();



private:
    //! DXGI(DirectX Graphics Infrastructure)Factoryを作成する
    IDXGIFactory4* CreateDXGIFactory();

    //! D3Dデバイスを作成する
    bool CreateD3DDevice(IDXGIFactory4* dxgiFactory);



private:
    /// <summary>
    /// GPUベンダー定義
    /// </summary>
    enum GPU_Vender {
        GPU_VenderNvidia,   //! NVIDIA
        GPU_VenderAMD,      //! Intel
        GPU_VenderIntel,    //! AMD
        Num_GPUVender,
    };

    std::vector<class RenderComponent*> _renderList;
    static Renderer* kInstance;

    ID3D12Device5* _d3d_device = nullptr;

};
