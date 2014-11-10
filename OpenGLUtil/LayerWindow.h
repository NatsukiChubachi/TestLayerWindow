#pragma once

#include <Windows.h>

/*! レイヤーウィンドウクラス
*/
class CLayerWindow
{
public:
	struct SWindowRect
	{
		int x, y;							// ウィンドウ位置
		int w, h;							// ウィンドウ幅
	};

public:
	CLayerWindow();							// コンストラクタ	
	~CLayerWindow();						// デストラクタ

	const HWND getHwnd();					// ウィンドウハンドル取得
	const SWindowRect &getWindowRect();		// ウィンドウ情報取得

	void InitWindow(
		const HINSTANCE &hInstance
		, WNDPROC  WndProc
		);									// ウィンドウ初期化

private:
	HINSTANCE m_hInstance;					// プロセスインスタンス
	HWND      m_hWnd;						// ウィンドウハンドル

	HGLRC     hRC;							// 描画用
	HDC       WinDC;						// 描画用デバイスコンテキスト

	SWindowRect m_SWindowRect;				// ウィンドウ情報

	bool      m_bInitialized;				// 初期化フラグ
};
