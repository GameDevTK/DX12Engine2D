/**
 * @file    Object.cpp
 * @author  tatsuki kanno
 * @date    2021/07/03
 * @brief   オブジェクトクラス
 * @details
 */

#include "Object.h"
#include "Component.h"

 /**
 * @brief   コンストラクタ
 */
Object::Object()
{

}

/**
 * @brief   デストラクタ
 */
Object::~Object()
{

}

/**
 * @brief       初期化関数
 * @details     初期化処理
 */
void Object::Initialize()
{

}

/**
 * @brief       更新関数
 * @details     更新処理
 */
void Object::Update()
{
    for (auto comp : components)
    {
        comp->Update();
    }
}

/**
 * @brief       終了処理関数
 * @details     終了時の終了処理
 */
void Object::Finalize()
{

}

/**
 * @brief       コンポーネントの追加
 * @details     コンポーネントの追加
 */
void Object::AddComponent(Component* component)
{
    components.push_back(component);
}

/**
 * @brief       コンポーネントの削除
 * @details     コンポーネントの削除
 */
void Object::RemoveComponent(Component* component)
{
    auto iter = std::find(components.begin(), components.end(), component);
    if(iter != components.end())
    {
        components.erase(iter);
    }
}

