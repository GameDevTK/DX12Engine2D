/**
 * @file    Object.h
 * @author  tatsuki kanno
 * @date    2021/07/03
 * @brief   オブジェクトクラス
 * @details
 */
#pragma once

#include "stdafx.h"

class Object
{
public:
    Object();
    ~Object();

    virtual void Initialize();
    virtual void Update();
    virtual void Finalize();

    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);

private:
    std::vector<class Component*> components;

};
