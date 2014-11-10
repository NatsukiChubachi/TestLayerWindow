#pragma once

#include <Windows.h>

/*! ���C���[�E�B���h�E�N���X
*/
class CLayerWindow
{
public:
	struct SWindowRect
	{
		int x, y;							// �E�B���h�E�ʒu
		int w, h;							// �E�B���h�E��
	};

public:
	CLayerWindow();							// �R���X�g���N�^	
	~CLayerWindow();						// �f�X�g���N�^

	const HWND getHwnd();					// �E�B���h�E�n���h���擾
	const SWindowRect &getWindowRect();		// �E�B���h�E���擾

	void InitWindow(
		const HINSTANCE &hInstance
		, WNDPROC  WndProc
		);									// �E�B���h�E������

private:
	HINSTANCE m_hInstance;					// �v���Z�X�C���X�^���X
	HWND      m_hWnd;						// �E�B���h�E�n���h��

	HGLRC     hRC;							// �`��p
	HDC       WinDC;						// �`��p�f�o�C�X�R���e�L�X�g

	SWindowRect m_SWindowRect;				// �E�B���h�E���

	bool      m_bInitialized;				// �������t���O
};
