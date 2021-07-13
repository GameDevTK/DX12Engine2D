/**
 * @file    Transform.h
 * @author  tatsuki kanno
 * @date    2021/07/03
 * @brief   トランスフォーム
 * @details ゲーム空間内での位置・回転・スケールを定義する構造体
 */
#pragma once

#include "stdafx.h"
#include "Math.h"

struct Transform
{
public:
    Transform();
    ~Transform();

public:
    Vector2 position;
    float scale;
    float rotation;

};
