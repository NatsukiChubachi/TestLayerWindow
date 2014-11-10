#include <process.h>

#include "WindowExecBase.h"

// CALLBACKはこんな感じ
LRESULT CALLBACK CWindowExecBase::WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    CWindowExecBase *pTarget = static_cast<CWindowExecBase*>(::GetProp(hWnd, CWINDOWEXECBASE_NAME));
    if(pTarget == NULL)
	{
		return ::DefWindowProc( hWnd,  uMsg, wParam, lParam );
	}

     return pTarget->WindowProc( hWnd,  uMsg, wParam, lParam );
}

LRESULT CWindowExecBase::WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	// ここに各メッセージの処理が入る
	switch( uMsg)
	{
	case WM_CREATE:

	case WM_DESTROY://!< ウインドウを閉じる
		::RemoveProp( hWnd, CWINDOWEXECBASE_NAME );
		::PostQuitMessage( 0 );//!< WM_QUITを送る
		return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
	default :
		return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
	}
	return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
}

// Threadはこんな感じ
unsigned __stdcall CWindowExecBase::Thread( void *p )
{
	// ここにスレッドの処理が入る
	CWindowExecBase *p1 = reinterpret_cast<CWindowExecBase*>( p );

	// 終了時にスレッドを殺しておく
	::_endthreadex( 0 );
	return 0;
}


void CWindowExecBase::SetWndProc(HWND hWnd)
{
	::SetProp( hWnd, CWINDOWEXECBASE_NAME, static_cast<HANDLE>(this) );
}


// 使用する関数の引数にCALLBACK関数があるなら
// そのまま渡すことになるかと
// Threadの起動はこんな感じ
#if 0
void CWindowExecBase::Start( void )
{
	/*
	// CALLBACK
	WNDCLASS wc;
	wc.lpfnWndProc = static_cast<WNDPROC>( WndProc );
	...
	...
	...
	::RegisterClass( &wc );

	::SetProp( m_hWnd, XXXX_NAME, static_cast<HANDLE>( this ) );
	*/
	/*
	// Thread
	unsigned int uiID;
	HANDLE hID;
	hID = reinterpret_cast<HANDLE>( ::_beginthreadex( NULL, 0, &Thread, this, 0, &uiID ) );
	::CloseHandle( hID );
	*/
}
#endif