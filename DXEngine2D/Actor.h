/**
 * @file    Actor.h
 * @author  tatsuki kanno
 * @date    2021/07/03
 * @brief   アクタークラス
 * @details
 */
#pragma once

#include "stdafx.h"
#include "Object.h"
#include "Transform.h"
#include "RenderComponent.h"

class Actor : public Object
{
public:
    Actor();
    ~Actor();

    virtual void Initialize();
    virtual void Update();
    virtual void Finalize();

private:
    Transform transform;


};
