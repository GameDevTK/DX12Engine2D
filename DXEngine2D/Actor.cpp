/**
 * @file    Actor.cpp
 * @author  tatsuki kanno
 * @date    2021/07/03
 * @brief   アクタークラス
 * @details
 */

#include "Actor.h"

/**
 * @brief   コンストラクタ
 */
Actor::Actor()
{

}

/**
 * @brief   デストラクタ
 */
Actor::~Actor()
{

}

/**
 * @brief       初期化関数
 * @details     初期化処理
 */
void Actor::Initialize()
{
    Object::Initialize();
}

/**
 * @brief       更新関数
 * @details     更新処理
 */
void Actor::Update()
{
    Object::Update();
}

/**
 * @brief       終了処理関数
 * @details     終了時の終了処理
 */
void Actor::Finalize()
{

}
