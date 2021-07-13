/**
 * @file    ObjectManager.h
 * @author  tatsuki kanno
 * @date    2021/07/03
 * @brief   オブジェクトクラス
 * @details
 */
#pragma once

#include "stdafx.h"
#include "Object.h"

class ObjectManager
{
public:
    ObjectManager();
    ~ObjectManager();

    virtual void Initialize();
    virtual void Update();
    virtual void Finalize();

    // オブジェクトを登録する
    void Register(Object* object);

private:

    std::vector<Object*> objList;

};
