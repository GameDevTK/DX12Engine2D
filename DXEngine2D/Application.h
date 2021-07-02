/**
 * @file    Application.h
 * @author  tatsuki kanno
 * @date    2021/07/02
 * @brief   ゲームアプリケーションの基盤となる抽象クラス
 * @details 
 */
#pragma once

#include "stdafx.h"

class Application
{
public:
    Application();
    ~Application();

    void boot();

protected:
    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual void finalize() = 0;

public:
    static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName);
    bool DispatchWindowMessage();

private:
    HWND hWnd;

};

