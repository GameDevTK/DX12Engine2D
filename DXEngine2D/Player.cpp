/**
 * @file    Player.cpp
 * @author  tatsuki kanno
 * @date    2021/07/03
 * @brief   プレイヤークラス
 * @details
 */

#include "Player.h"
#include "Sprite.h"

/**
 * @brief   コンストラクタ
 */
Player::Player()
    : sprite(nullptr)
{

}

/**
 * @brief   デストラクタ
 */
Player::~Player()
{

}

/**
 * @brief       初期化関数
 * @details     初期化処理
 */
void Player::Initialize()
{
    Actor::Initialize();
    sprite = new Sprite();
    AddComponent(sprite);
}

/**
 * @brief       更新関数
 * @details     更新処理
 */
void Player::Update()
{
    Actor::Update();
}

/**
 * @brief       終了処理関数
 * @details     終了時の終了処理
 */
void Player::Finalize()
{
    RemoveComponent(sprite);
}
