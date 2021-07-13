/**
 * @file    SampleGame.h
 * @author  tatsuki kanno
 * @date    2021/07/02
 * @brief   ゲームのメインクラスのサンプル
 * @details
 */
#pragma once

#include "Application.h"

class SampleGame : public Application
{
public:
    SampleGame();
    ~SampleGame();

    void Initialize();
    void Update();
    void Finalize();

private:
    class Player* player;


};

