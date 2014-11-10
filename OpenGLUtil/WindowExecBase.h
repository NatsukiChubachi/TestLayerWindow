#pragma once

#include <Windows.h>

static const wchar_t* const CWINDOWEXECBASE_NAME = L"CWindowExecBase";	//!< Prop–¼

class CWindowExecBase
{
public:
	CWindowExecBase(){};
	~CWindowExecBase(){};

    //void Start( void );
	void SetWndProc(HWND hWnd);
    void Loop( void ){}

private:
    static LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	LRESULT WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	static unsigned __stdcall Thread( void * );

};

