/**
 * @file    Sprite.cpp
 * @author  tatsuki kanno
 * @date    2021/07/03
 * @brief   矩形クラス
 * @details
 */

#include "Sprite.h"

/**
 * @brief   コンストラクタ
 */
Sprite::Sprite()
    : transform (nullptr)
{

}

/**
 * @brief   デストラクタ
 */
Sprite::~Sprite()
{

}

/**
 * @brief       初期化関数
 * @details     初期化処理
 */
void Sprite::Initialize()
{

}

/**
 * @brief       更新関数
 * @details     更新処理
 */
void Sprite::Update()
{
    RenderComponent::Update();

}

/**
 * @brief       終了処理関数
 * @details     終了時の終了処理
 */
void Sprite::Finalize()
{

}
