/**
 * @file    Transform.cpp
 * @author  tatsuki kanno
 * @date    2021/07/03
 * @brief   トランスフォーム
 * @details ゲーム空間内での位置・回転・スケールを定義する構造体
 */

#include "Transform.h"

/**
 * @brief   コンストラクタ
 */
Transform::Transform()
    : position(Vector2::Zero)
    , scale(1.0f)
    , rotation(0.0f)
{

}

/**
 * @brief   デストラクタ
 */
Transform::~Transform()
{

}
