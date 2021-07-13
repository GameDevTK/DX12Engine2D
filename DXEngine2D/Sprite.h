/**
 * @file    Sprite.h
 * @author  tatsuki kanno
 * @date    2021/07/03
 * @brief   矩形クラス
 * @details
 */
#pragma once

#include "stdafx.h"
#include "Transform.h"
#include "RenderComponent.h"

class Sprite : public RenderComponent
{
public:
    Sprite();
    ~Sprite();

    virtual void Initialize();
    virtual void Update();
    virtual void Finalize();

private:
    const Transform* transform;


};
