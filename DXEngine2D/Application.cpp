/**
 * @file    Application.cpp
 * @author  tatsuki kanno
 * @date    2021/07/02
 * @brief   ゲームアプリケーションの基盤となる抽象クラス
 * @details 
 */

#include "stdafx.h"
#include "Application.h"

/**
 * @brief   コンストラクタ
 */
Application::Application()
    : hWnd  (NULL)
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
void Application::boot()
{
    initialize();

    while (DispatchWindowMessage())
    {
        // オブジェクトの更新
        update();

        // ドローコール
    }

    finalize();

}

/**
 * @brief	メッセージプロシージャ
 * @param[in]	hWnd	メッセージを送ってきたウィンドウのハンドル
 * @param[in]	msg		メッセージの種類
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

//==============================================================================
// ウィンドウの初期化
//==============================================================================
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
    hWnd = CreateWindow(
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

    ShowWindow(hWnd,nCmdShow);

}

//==============================================================================
// ウィンドウメッセージをディスパッチ
//==============================================================================
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