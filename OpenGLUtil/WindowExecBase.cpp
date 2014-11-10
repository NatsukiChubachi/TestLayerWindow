#include <process.h>

#include "WindowExecBase.h"

// CALLBACK�͂���Ȋ���
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
	// �����Ɋe���b�Z�[�W�̏���������
	switch( uMsg)
	{
	case WM_CREATE:

	case WM_DESTROY://!< �E�C���h�E�����
		::RemoveProp( hWnd, CWINDOWEXECBASE_NAME );
		::PostQuitMessage( 0 );//!< WM_QUIT�𑗂�
		return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
	default :
		return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
	}
	return ::DefWindowProc( hWnd, uMsg, wParam, lParam );
}

// Thread�͂���Ȋ���
unsigned __stdcall CWindowExecBase::Thread( void *p )
{
	// �����ɃX���b�h�̏���������
	CWindowExecBase *p1 = reinterpret_cast<CWindowExecBase*>( p );

	// �I�����ɃX���b�h���E���Ă���
	::_endthreadex( 0 );
	return 0;
}


void CWindowExecBase::SetWndProc(HWND hWnd)
{
	::SetProp( hWnd, CWINDOWEXECBASE_NAME, static_cast<HANDLE>(this) );
}


// �g�p����֐��̈�����CALLBACK�֐�������Ȃ�
// ���̂܂ܓn�����ƂɂȂ邩��
// Thread�̋N���͂���Ȋ���
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