
#include <crtdbg.h>

#include <windows.h>
#include <GL/gl.h>

//#include "../OpenGLUtil/LayerWindow.h"
#include "WndProcBase.h"

//CLayerWindow layerWindow;


/*! メイン関数
*/
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
   // メモリリーク検出
   _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ウィンドウの初期化
	CWndProcBase::Initialize(hInstance);

	// メッセージループ
	MSG  msg;
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

