/**
 * @file    Player.h
 * @author  tatsuki kanno
 * @date    2021/07/03
 * @brief   プレイヤークラス
 * @details
 */
#pragma once

#include "Actor.h"

class Player : public Actor
{
public:
    Player();
    ~Player();

    void Initialize();
    void Update();
    void Finalize();

private:
    class Sprite* sprite;

};
