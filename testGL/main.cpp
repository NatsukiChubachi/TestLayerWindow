
#include <crtdbg.h>

#include <windows.h>
#include <GL/gl.h>

//#include "../OpenGLUtil/LayerWindow.h"
#include "WndProcBase.h"

//CLayerWindow layerWindow;


/*! ���C���֐�
*/
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
   // ���������[�N���o
   _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// �E�B���h�E�̏�����
	CWndProcBase::Initialize(hInstance);

	// ���b�Z�[�W���[�v
	MSG  msg;
	while (GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

