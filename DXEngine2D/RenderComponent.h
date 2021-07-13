/**
 * @file    RenderComponent.h
 * @author  tatsuki kanno
 * @date    2021/07/03
 * @brief   矩形クラス
 * @details
 */
#pragma once

#include "stdafx.h"
#include "Component.h"

class RenderComponent : public Component
{
public:
    RenderComponent();
    ~RenderComponent();

    virtual void Initialize();
    virtual void Update();
    virtual void Finalize();

private:


};
