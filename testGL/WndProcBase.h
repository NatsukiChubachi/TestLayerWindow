#pragma once

#include <windows.h>
#include <GL/gl.h>

#include <map>

#include "../OpenGLUtil/LayerWindow.h"


/*! ウィンドウプロシージャ自作クラス
*/
class CWndProcBase
{
protected:
	enum ENUM_BUTTONTYPE
	{
		BUTTONTYPE_NONE = 0,								// なし
		BUTTONTYPE_DOWN,									// DOWN
		BUTTONTYPE_UP,										// UP
		BUTTONTYPE_DBLCLICK									// DoubleClick
	};

public:
	struct SObject
	{
		double dPosX, dPosY, dPosZ;
		double dPosX_2, dPosY_2, dPosZ_2;
		double dRotZ;
		double dScaleZ;
		int iIndex;
	};

public:
	CWndProcBase();											// コンストラクタ
	~CWndProcBase();										// デストラクタ

	static void Initialize(HINSTANCE hInstance);			// 初期化

public:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// ウィンドウプロシージャ

private:
	static void EventCreateWindow(HWND hWnd);				// ウィンドウ生成イベント
	static void EventDestroyWindow();						// ウィンドウ破棄イベント
	static void EventKey(WPARAM wParam, LPARAM lParam, ENUM_BUTTONTYPE eType);		// キーイベント
	static void EventLButton(WPARAM wParam, LPARAM lParam, ENUM_BUTTONTYPE eType);	// マウス左クリックイベント
	static void EventRButton(WPARAM wParam, LPARAM lParam, ENUM_BUTTONTYPE eType);	// マウス右クリックイベント
	static void EventMButton(WPARAM wParam, LPARAM lParam, ENUM_BUTTONTYPE eType);	// マウス右クリックイベント
	static void EventPaintWindow();							// ウィンドウ描画イベント

protected:
	static void LoadResource();								// リソースロード
	static void KeyEvent(WPARAM wParam, LPARAM lParam, ENUM_BUTTONTYPE eType);		// キーイベント
	static void LButton(WPARAM wParam, int x, int y, ENUM_BUTTONTYPE eType);		// マウス左クリック
	static void RButton(WPARAM wParam, int x, int y, ENUM_BUTTONTYPE eType);		// マウス右クリック
	static void MButton(WPARAM wParam, int x, int y, ENUM_BUTTONTYPE eType);		// マウス中クリック
	static void Draw();										// 描画

	static void DrawTexture( double dX, double dY, double dZ, double dA, double dE, GLuint iIndex );

private:
	static HDC    WinDC;									// ウィンドウデバイスコンテキスト
	static HGLRC  hRC;										// 描画先デバイスコンテキスト
	static GLuint g_texID;									// テクスチャID

	static std::map<GLuint, GLuint> m_mapTexId;

	static CLayerWindow m_LayerWindow;

	static SObject m_SObject[24];
};

