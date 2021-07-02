/** 
 * @file    stdfx.h
 * @author  tatsuki kanno
 * @date    2021/07/02
 * @brief   プリコンパイル済みヘッダーをincludeしたヘッダーファイル
 * @details 頻繁に使われるが、変更は頻繁でないインクルードファイルのためのインクルードファイル
 *          このファイルの中で_AFX_NO_XXXというマクロを定義してはいけない
 * @ref     https://qiita.com/exp/items/5ff3099f4878d2fe2ecb
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <math.h>
#include <vector>
#include <list>
#include <D3DCompiler.h>
#include <Windows.h>
#include <d3d12.h>
#include <map>
#include <functional>
#include <algorithm>
#include <DirectXMath.h>
#include <Xinput.h>
#include <array>

/**
 * @brief       安全なdeleteをするテンプレート関数
 * @param[in]   p deleteしたいオブジェクトポインタ
 * @return      void
 * @details     delete処理後、nullptrで初期化
*/
template <class T>
inline void SafeDelete(T*& p) {
    delete p;
    p = nullptr;
}

/**
 * @brief       安全なreleaseをするテンプレート関数
 * @param[in]   p releaseしたいオブジェクトポインタ
 * @return      void
 * @details     delete処理後、nullptrで初期化
*/
template <class T>
inline void SafeRelease(T*& p) {
    p->Release();
    p = nullptr;
}

/**
 * @def     FRAME_BUFFER_
 * @brief   フレームバッファのサイズ
 * @details 現在はウィンドウサイズに利用
 */
const UINT FRAME_BUFFER_W = 1280;	//! フレームバッファの幅
const UINT FRAME_BUFFER_H = 720;	//! フレームバッファの高さ
