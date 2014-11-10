#include "LayerWindow.h"
#include <GL/gl.h>

/*! �R���X�g���N�^
*/
CLayerWindow::CLayerWindow()
{
	m_bInitialized = false;
}

/*! �f�X�g���N�^
*/
CLayerWindow::~CLayerWindow()
{
}

/*! �E�B���h�E�n���h���擾
@retval HWND �E�B���h�E�n���h��
*/
const HWND CLayerWindow::getHwnd()
{
	return m_hWnd;
}

/*! �E�B���h�E���擾
@retval CLayerWindow::SWindowRect �E�B���h�E���
*/
const CLayerWindow::SWindowRect &CLayerWindow::getWindowRect()
{
	return m_SWindowRect;
}

/*! �E�B���h�E������
*/
void CLayerWindow::InitWindow(
					const HINSTANCE &hInstance			//!< in �v���Z�X�n���h��
					, WNDPROC  WndProc					//!< in �v���V�[�W���֐�
					)
{
	WNDCLASS wndclass;

	m_hInstance = hInstance;							// �v���Z�X�̃n���h����ۑ�

	wndclass.style         = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc   = WndProc;
	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = 0;
	wndclass.hInstance     = hInstance;
	wndclass.hIcon         = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor       = LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName  = NULL;
	wndclass.lpszClassName = L"CWindow";

	::RegisterClass(&wndclass);

	// �E�B���h�E���̎擾
	int x = GetSystemMetrics(SM_XVIRTUALSCREEN) - 10;
	int y = GetSystemMetrics(SM_YVIRTUALSCREEN) - 10;
	int w = GetSystemMetrics(SM_CXVIRTUALSCREEN) + 20;
	int h = GetSystemMetrics(SM_CYVIRTUALSCREEN) + 20;

	// �E�B���h�E���̎擾
	m_SWindowRect.x = x;
	m_SWindowRect.y = y;
	m_SWindowRect.w = w;
	m_SWindowRect.h = h;

	// �E�B���h�E�̕\��
	// Layered�E�B���h�E�ō쐬���A���j���[�g���O��
	m_hWnd = CreateWindowEx (
		WS_EX_LAYERED | WS_EX_NOACTIVATE | WS_EX_TOPMOST,
		L"CWindow",L"OpenGL�\���e�X�g",WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, w, h,
        NULL, NULL, hInstance, NULL
		);

	ShowWindow(m_hWnd, SW_HIDE);
	SetMenu(m_hWnd, NULL);										//���j���[���B��
	SetWindowLong(m_hWnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);	//�E�B���h�E�̃X�^�C����ύX
	
	MoveWindow(
		m_hWnd
		, x, y, w, h
		, FALSE
		);														//�E�B���h�E����ʂɍ��킹��

	//::SetProp( m_hWnd, CLAYERWINDOW_NAME, static_cast<HANDLE>( this ) );
	//CLayerWindow *pTarget = static_cast<CLayerWindow*>( ::GetProp( m_hWnd, CLAYERWINDOW_NAME ) );
	//this->EventCreateWindow(m_hWnd);
}
