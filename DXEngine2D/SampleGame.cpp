/**
 * @file    SampleGame.cpp
 * @author  tatsuki kanno
 * @date    2021/07/02
 * @brief   ゲームのメインクラスのサンプル
 * @details
 */

#include "SampleGame.h"
#include "Player.h"

/**
 * @brief   コンストラクタ
 */
SampleGame::SampleGame()
    :player(nullptr)
{

}

/**
 * @brief   デストラクタ
 */
SampleGame::~SampleGame()
{

}

/**
 * @brief       初期化関数
 * @details     ゲームアプリケーション起動時の初期化処理
 */
void SampleGame::Initialize()
{
    player = new Player();
    player->Initialize();
    // プレイヤーを作成
    RegisterObject(player);

}

/**
 * @brief       更新関数
 * @details     ゲームアプリケーションの更新処理
 */
void SampleGame::Update()
{

}

/**
 * @brief       終了処理関数
 * @details     ゲームアプリケーション終了時の終了処理
 */
void SampleGame::Finalize()
{

}
