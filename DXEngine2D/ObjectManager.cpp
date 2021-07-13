/**
 * @file    ObjectManager.cpp
 * @author  tatsuki kanno
 * @date    2021/07/03
 * @brief   オブジェクトクラス
 * @details
 */

#include "ObjectManager.h"

/**
 * @brief   コンストラクタ
 */
ObjectManager::ObjectManager()
{

}

/**
 * @brief   デストラクタ
 */
ObjectManager::~ObjectManager()
{

}

/**
 * @brief       初期化関数
 * @details     初期化処理
 */
void ObjectManager::Initialize()
{

}

/**
 * @brief       更新関数
 * @details     更新処理
 */
void ObjectManager::Update()
{
    for (auto object : objList)
    {
        object->Update();
    }
}

/**
 * @brief       終了処理関数
 * @details     終了時の終了処理
 */
void ObjectManager::Finalize()
{
    for (auto obj : objList)
    {
        SafeDelete(obj);
    }
}

/**
 * @brief       オブジェクトを登録する
 * @details     
 */
void ObjectManager::Register(Object* object)
{
    objList.push_back(object);
}

