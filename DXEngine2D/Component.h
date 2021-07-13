/**
 * @file    Component.h
 * @author  tatsuki kanno
 * @date    2021/07/03
 * @brief   オブジェクトクラス
 * @details
 */
#pragma once

#include "stdafx.h"
#include "Object.h"

class Component
{
public:
    Component();
    virtual ~Component();

    virtual void Initialize();
    virtual void Update();
    virtual void Finalize();

private:

};
