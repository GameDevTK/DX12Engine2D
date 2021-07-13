/**
 * @file    main.cpp
 * @author  tatsuki kanno
 * @date    2021/07/02
 * @brief   エントリポイント
 * @details 
 */

#include "stdafx.h"
#include "SampleGame.h"

 /**
  * @brief      エントリポイント
  * @details    ゲームアプリケーション起動時の初期化処理
  */
int WINAPI wWinMain(
    _In_ HINSTANCE hInstance, 
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine, 
    _In_ int nCmdShow)
{

    Application* game;

    game = new SampleGame();

    game->InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

    game->Boot();

    SafeDelete(game);

    return 0;
}