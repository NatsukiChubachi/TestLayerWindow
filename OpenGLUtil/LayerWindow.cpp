#include "LayerWindow.h"
#include <GL/gl.h>

/*! コンストラクタ
*/
CLayerWindow::CLayerWindow()
{
	m_bInitialized = false;
}

/*! デストラクタ
*/
CLayerWindow::~CLayerWindow()
{
}

/*! ウィンドウハンドル取得
@retval HWND ウィンドウハンドル
*/
const HWND CLayerWindow::getHwnd()
{
	return m_hWnd;
}

/*! ウィンドウ情報取得
@retval CLayerWindow::SWindowRect ウィンドウ情報
*/
const CLayerWindow::SWindowRect &CLayerWindow::getWindowRect()
{
	return m_SWindowRect;
}

/*! ウィンドウ初期化
*/
void CLayerWindow::InitWindow(
					const HINSTANCE &hInstance			//!< in プロセスハンドル
					, WNDPROC  WndProc					//!< in プロシージャ関数
					)
{
	WNDCLASS wndclass;

	m_hInstance = hInstance;							// プロセスのハンドルを保存

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

	// ウィンドウ情報の取得
	int x = GetSystemMetrics(SM_XVIRTUALSCREEN) - 10;
	int y = GetSystemMetrics(SM_YVIRTUALSCREEN) - 10;
	int w = GetSystemMetrics(SM_CXVIRTUALSCREEN) + 20;
	int h = GetSystemMetrics(SM_CYVIRTUALSCREEN) + 20;

	// ウィンドウ幅の取得
	m_SWindowRect.x = x;
	m_SWindowRect.y = y;
	m_SWindowRect.w = w;
	m_SWindowRect.h = h;

	// ウィンドウの表示
	// Layeredウィンドウで作成し、メニュー枠を外す
	m_hWnd = CreateWindowEx (
		WS_EX_LAYERED | WS_EX_NOACTIVATE | WS_EX_TOPMOST,
		L"CWindow",L"OpenGL表示テスト",WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, w, h,
        NULL, NULL, hInstance, NULL
		);

	ShowWindow(m_hWnd, SW_HIDE);
	SetMenu(m_hWnd, NULL);										//メニューを隠す
	SetWindowLong(m_hWnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);	//ウィンドウのスタイルを変更
	
	MoveWindow(
		m_hWnd
		, x, y, w, h
		, FALSE
		);														//ウィンドウを画面に合わせる

	//::SetProp( m_hWnd, CLAYERWINDOW_NAME, static_cast<HANDLE>( this ) );
	//CLayerWindow *pTarget = static_cast<CLayerWindow*>( ::GetProp( m_hWnd, CLAYERWINDOW_NAME ) );
	//this->EventCreateWindow(m_hWnd);
}
