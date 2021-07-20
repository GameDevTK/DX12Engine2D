/**
 * @file    Application.cpp
 * @author  tatsuki kanno
 * @date    2021/07/02
 * @brief   ゲームアプリケーションの基盤となる抽象クラス
 * @details 
 */

#include "stdafx.h"
#include "Application.h"
#include "ObjectManager.h"
#include "Renderer.h"

/**
 * @brief   コンストラクタ
 */
Application::Application()
    : _hwnd         (NULL)
    , objectManager (nullptr)
    , renderer      (nullptr)
{

}

/**
 * @brief   デストラクタ
 */
Application::~Application()
{

}

/**
 * @brief       初期化関数
 * @details     ゲームアプリケーション起動時の初期化処理
 */
void Application::Boot()
{
    InitializeSystem();

    // 継承先のゲームの初期化
    Initialize();

    while (DispatchWindowMessage())
    {
        // 共通システム更新
        UpdateSystem();

        // 継承先のゲーム更新
        Update();

        // ドローコール
        //renderer->Update()

    }

    Finalize();

}

/**
 * @brief       システムの初期化
 * @details     ゲームに依存しない共通初期化処理
 */
void Application::InitializeSystem()
{
  Renderer::InitData data;
  data.hwnd = _hwnd;
  data.frameBufferWidth = FRAME_BUFFER_W;
  data.frameBufferHeight = FRAME_BUFFER_H;
  renderer = new Renderer(data);
  renderer->Initialize();

  objectManager = new ObjectManager();
  objectManager->Initialize();


}

/**
 * @brief       システムの更新
 * @details     ゲームに依存しない共通更新処理
 */
void Application::UpdateSystem()
{
    // オブジェクトマネージャーの更新
    objectManager->Update();
}

/**
 * @brief       システムの終了処理
 * @details     ゲームに依存しない共通終了処理
 */
void Application::FinalizeSystem()
{
    objectManager->Finalize();
    SafeDelete(objectManager);

    renderer->Finalize();
    SafeDelete(renderer);

}

/**
 * @brief       メッセージプロシージャ
 * @param[in]   hWnd    メッセージを送ってきたウィンドウのハンドル
 * @param[in]   msg     メッセージの種類
 * wParamとlParamは引数
 */
LRESULT CALLBACK Application::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // 送られてきたメッセージで処理を分岐させる。
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
}

/**
 * @brief   ウィンドウの初期化
 */
void Application::InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName)
{
    // ウィンドウクラスのパラメータを設定
    WNDCLASSEX wc =
    {
        sizeof(WNDCLASSEX),
        CS_CLASSDC,
        MsgProc,
        0,
        0,
        GetModuleHandle(NULL),
        NULL,
        NULL,
        NULL,
        NULL,
        appName,
        NULL
    };

    // ウィンドウクラスの登録
    RegisterClassEx(&wc);

    // ウィンドウの作成
    _hwnd = CreateWindow(
        appName,
        appName,
        WS_OVERLAPPEDWINDOW,
        0,
        0,
        FRAME_BUFFER_W,
        FRAME_BUFFER_H,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    ShowWindow(_hwnd,nCmdShow);

}

/**
 * @brief   ウィンドウメッセージをディスパッチ
 */
bool Application::DispatchWindowMessage()
{
    MSG msg = { 0 };
    while (WM_QUIT != msg.message) {
        // ウィンドウからのメッセージを受け取る
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // ウィンドウメッセージが空になった
            break;
        }
    }
    return msg.message != WM_QUIT;
}

/**
 * @brief       生成したオブジェクトを、マネージャーに登録する
 * @param[in]   object  登録するオブジェクトのポインタ
 */
void Application::RegisterObject(Object* object)
{
    objectManager->Register(object);
}
