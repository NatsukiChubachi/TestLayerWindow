#pragma once

#include <windows.h>
#include <GL/gl.h>

#include <map>

#include "../OpenGLUtil/LayerWindow.h"


/*! �E�B���h�E�v���V�[�W������N���X
*/
class CWndProcBase
{
protected:
	enum ENUM_BUTTONTYPE
	{
		BUTTONTYPE_NONE = 0,								// �Ȃ�
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
	CWndProcBase();											// �R���X�g���N�^
	~CWndProcBase();										// �f�X�g���N�^

	static void Initialize(HINSTANCE hInstance);			// ������

public:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �E�B���h�E�v���V�[�W��

private:
	static void EventCreateWindow(HWND hWnd);				// �E�B���h�E�����C�x���g
	static void EventDestroyWindow();						// �E�B���h�E�j���C�x���g
	static void EventKey(WPARAM wParam, LPARAM lParam, ENUM_BUTTONTYPE eType);		// �L�[�C�x���g
	static void EventLButton(WPARAM wParam, LPARAM lParam, ENUM_BUTTONTYPE eType);	// �}�E�X���N���b�N�C�x���g
	static void EventRButton(WPARAM wParam, LPARAM lParam, ENUM_BUTTONTYPE eType);	// �}�E�X�E�N���b�N�C�x���g
	static void EventMButton(WPARAM wParam, LPARAM lParam, ENUM_BUTTONTYPE eType);	// �}�E�X�E�N���b�N�C�x���g
	static void EventPaintWindow();							// �E�B���h�E�`��C�x���g

protected:
	static void LoadResource();								// ���\�[�X���[�h
	static void KeyEvent(WPARAM wParam, LPARAM lParam, ENUM_BUTTONTYPE eType);		// �L�[�C�x���g
	static void LButton(WPARAM wParam, int x, int y, ENUM_BUTTONTYPE eType);		// �}�E�X���N���b�N
	static void RButton(WPARAM wParam, int x, int y, ENUM_BUTTONTYPE eType);		// �}�E�X�E�N���b�N
	static void MButton(WPARAM wParam, int x, int y, ENUM_BUTTONTYPE eType);		// �}�E�X���N���b�N
	static void Draw();										// �`��

	static void DrawTexture( double dX, double dY, double dZ, double dA, double dE, GLuint iIndex );

private:
	static HDC    WinDC;									// �E�B���h�E�f�o�C�X�R���e�L�X�g
	static HGLRC  hRC;										// �`���f�o�C�X�R���e�L�X�g
	static GLuint g_texID;									// �e�N�X�`��ID

	static std::map<GLuint, GLuint> m_mapTexId;

	static CLayerWindow m_LayerWindow;

	static SObject m_SObject[24];
};

