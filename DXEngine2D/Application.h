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

    void Boot();

    // Window
    static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void InitWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, const TCHAR* appName);
    bool DispatchWindowMessage();

    // ObjectManager
    void RegisterObject(class Object* object);

protected:
    virtual void Initialize() = 0;
    virtual void Update() = 0;
    virtual void Finalize() = 0;

private:
    // Sysytem
    void InitializeSystem();
    void UpdateSystem();
    void FinalizeSystem();

protected:
    class ObjectManager* objectManager;
    class Renderer* renderer;

private:

    HWND hWnd;

};

