

#include "WndProcBase.h"
#include <gl/GLU.h>

#include "../OpenGLUtil/BMPImage.h"

#include <time.h>


HDC    CWndProcBase::WinDC   = NULL;
HGLRC  CWndProcBase::hRC     = NULL;

GLuint CWndProcBase::g_texID = 0;

std::map<GLuint, GLuint> CWndProcBase::m_mapTexId;

CLayerWindow CWndProcBase::m_LayerWindow;

CWndProcBase::SObject CWndProcBase::m_SObject[24];

/*! コンストラクタ
*/
CWndProcBase::CWndProcBase()
{
}


/*! デストラクタ
*/
CWndProcBase::~CWndProcBase()
{
}


/*! 初期化
*/
void CWndProcBase::Initialize(HINSTANCE hInstance)
{
	srand((unsigned int)time(NULL));

	// ウィンドウの初期化
	m_LayerWindow.InitWindow(hInstance, CWndProcBase::WndProc);

	// オブジェクトの初期化
	for(int i=0; i<12; ++i)
	{
		int iIndex = i;
		m_SObject[iIndex].dPosX = (1.8*(i-6))+0.90;
		m_SObject[iIndex].dPosY = +4.0;
		m_SObject[iIndex].dPosZ = 0.0;

		m_SObject[iIndex].dPosX_2 = 0.0;
		m_SObject[iIndex].dPosY_2 = 0.0;
		m_SObject[iIndex].dPosZ_2 = 0.0;

		m_SObject[iIndex].dRotZ = 0.0;
		m_SObject[iIndex].dScaleZ = 1.25;
		m_SObject[iIndex].iIndex = 101+(rand()%24);
	}

	for(int i=0; i<12; ++i)
	{
		int iIndex = i+12;
		m_SObject[iIndex].dPosX = (1.8*(i-6))+0.90;
		m_SObject[iIndex].dPosY = -4.0;
		m_SObject[iIndex].dPosZ = 0.0;

		m_SObject[iIndex].dPosX_2 = 0.0;
		m_SObject[iIndex].dPosY_2 = 0.0;
		m_SObject[iIndex].dPosZ_2 = 0.0;

		m_SObject[iIndex].dRotZ = 0.0;
		m_SObject[iIndex].dScaleZ = 1.25;
		m_SObject[iIndex].iIndex = 101+(rand()%24);
	}
}


/*! ウィンドウプロシージャ
*/
LRESULT CALLBACK CWndProcBase::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) 
	{
	case WM_CREATE:										// ウィンドウ生成イベント
		{
			EventCreateWindow(hWnd);
			LoadResource();								// リソースロード
			return 0;
		}
		break;

	case WM_DESTROY :									// ウィンドウ破棄イベント
		{
			EventDestroyWindow();
			return 0;
		}
		break;

	case WM_PAINT:										// ウィンドウ描画
		{
			EventPaintWindow();
			return 0;
		}
		break;

	case WM_KEYDOWN:									// キー押下時
		EventKey(wParam, lParam, BUTTONTYPE_DOWN);
		break;
	case WM_KEYUP:										// キー押上時
		EventKey(wParam, lParam, BUTTONTYPE_UP);
		break;

	case WM_LBUTTONDOWN:								// 左クリック押下時
		EventLButton(wParam, lParam, BUTTONTYPE_DOWN);
		break;
	case WM_LBUTTONUP:									// 左クリック押上時
		EventLButton(wParam, lParam, BUTTONTYPE_UP);
		break;
	case WM_LBUTTONDBLCLK:								// 左ダブルクリック時
		EventLButton(wParam, lParam, BUTTONTYPE_DBLCLICK);
		break;

	case WM_MBUTTONDOWN:								// 右クリック押下時
		EventRButton(wParam, lParam, BUTTONTYPE_DOWN);
		break;
	case WM_MBUTTONUP:									// 右クリック押上時
		EventRButton(wParam, lParam, BUTTONTYPE_UP);
		break;
	case WM_MBUTTONDBLCLK:								// 右ダブルクリック時
		EventRButton(wParam, lParam, BUTTONTYPE_DBLCLICK);
		break;

	case WM_RBUTTONDOWN:								// 中クリック押下時
		EventMButton(wParam, lParam, BUTTONTYPE_DOWN);
		break;
	case WM_RBUTTONUP:									// 中クリック押上時
		EventMButton(wParam, lParam, BUTTONTYPE_DOWN);
		break;
	case WM_RBUTTONDBLCLK:								// 中ダブルクリック時
		EventMButton(wParam, lParam, BUTTONTYPE_DOWN);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam) ;
}


/*! CreateWindowイベント
*/
void CWndProcBase::EventCreateWindow(HWND hWnd)
{
	int pixelFormat;

	PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR),		// size of this pfd 
		1,									// version number 
		PFD_DRAW_TO_WINDOW |				// support window 
		PFD_SUPPORT_OPENGL |				// support OpenGL 
		PFD_DOUBLEBUFFER,					// double buffered 
		PFD_TYPE_RGBA,						// RGBA type 
		24,									// 24-bit color depth 
		0, 0, 0, 0, 0, 0,					// color bits ignored 
		0,									// no alpha buffer 
		0,									// shift bit ignored 
		0,									// no accumulation buffer 
		0, 0, 0, 0,							// accum bits ignored 
		32,									// 32-bit z-buffer 
		0,									// no stencil buffer 
		0,									// no auxiliary buffer 
		PFD_MAIN_PLANE,						// main layer 
		0,									// reserved 
		0, 0, 0								// layer masks ignored 
	}; 

	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

	WinDC = GetDC(hWnd);

	pixelFormat = ChoosePixelFormat(WinDC, &pfd);
	SetPixelFormat(WinDC, pixelFormat,&pfd);

	hRC = wglCreateContext(WinDC);
	wglMakeCurrent(WinDC, hRC);


	const CLayerWindow::SWindowRect &rect = m_LayerWindow.getWindowRect();
	glViewport( rect.x, rect.y, rect.w, rect.h );
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	GLdouble aspect = (GLdouble)(rect.w) / (GLdouble)(rect.h);
    gluPerspective(60.0, aspect, 1.0, 200.0);
}


/*! DestroyWindowイベント
*/
void CWndProcBase::EventDestroyWindow()
{
	wglMakeCurrent(WinDC, 0);
	wglDeleteContext(hRC);
	PostQuitMessage(0);
}


/*! キーイベント
*/
void CWndProcBase::EventKey(WPARAM wParam, LPARAM lParam, ENUM_BUTTONTYPE eType)
{
	KeyEvent(wParam, lParam, eType);			// キーイベント
}


/*! マウス左クリックイベント
*/
void CWndProcBase::EventLButton(WPARAM wParam, LPARAM lParam, ENUM_BUTTONTYPE eType)
{
	int x = lParam & 0xFFFF;
	int y = (lParam >> 16) & 0xFFFF;
	LButton(wParam, x, y, eType);				// マウス左クリック処理
}


/*! マウス右クリックイベント
*/
void CWndProcBase::EventRButton(WPARAM wParam, LPARAM lParam, ENUM_BUTTONTYPE eType)
{
	int x = lParam & 0xFFFF;
	int y = (lParam >> 16) & 0xFFFF;
	RButton(wParam, x, y, eType);				// マウス左クリック処理
}


/*! マウス中クリックイベント
*/
void CWndProcBase::EventMButton(WPARAM wParam, LPARAM lParam, ENUM_BUTTONTYPE eType)
{
	int x = lParam & 0xFFFF;
	int y = (lParam >> 16) & 0xFFFF;
	MButton(wParam, x, y, eType);				// マウス左クリック処理
}


/*! PaintWidnowイベント
*/
void CWndProcBase::EventPaintWindow()
{
	Draw();
}


/*! リソースロード
*/
void CWndProcBase::LoadResource()
{
	// 画像データのロード
	//glEnable(GL_TEXTURE_2D);
	CBMPImage bmpi;
	g_texID = bmpi.load( "dat\\test.bmp" );

	GLuint iTmp;
	iTmp = bmpi.load( "dat\\clock_frame.bmp" );
	m_mapTexId.insert( map<GLuint, GLuint>::value_type( 1, iTmp ) );

	iTmp = bmpi.load( "dat\\clock_bar1.bmp" );
	m_mapTexId.insert( map<GLuint, GLuint>::value_type( 2, iTmp ) );

	iTmp = bmpi.load( "dat\\clock_bar2.bmp" );
	m_mapTexId.insert( map<GLuint, GLuint>::value_type( 3, iTmp ) );

	{
		bmpi.setColorKey( 0, 255, 0 );

		char cTmp[50];

		for(int i=1; i<=24; ++i)
		{
			sprintf(cTmp, "dat\\do_%d.bmp", i);
			iTmp = bmpi.load( cTmp );
			m_mapTexId.insert( map<GLuint, GLuint>::value_type( 100+i, iTmp ) );
		}

		for(int i=1; i<=24; ++i)
		{
			sprintf(cTmp, "dat\\go_%d.bmp", i);
			iTmp = bmpi.load( cTmp );
			m_mapTexId.insert( map<GLuint, GLuint>::value_type( 200+i, iTmp ) );
		}

		for(int i=1; i<=1; ++i)
		{
			sprintf(cTmp, "dat\\me_%d.bmp", i);
			iTmp = bmpi.load( cTmp );
			m_mapTexId.insert( map<GLuint, GLuint>::value_type( 300+i, iTmp ) );
		}
	}
}


/*! キーイベント
*/
void CWndProcBase::KeyEvent(WPARAM wParam, LPARAM lParam, ENUM_BUTTONTYPE eType)
{
}


/*! マウス左クリック
*/
void CWndProcBase::LButton(WPARAM wParam, int x, int y, ENUM_BUTTONTYPE eType)
{
	PostQuitMessage(0);
}


/*! マウス右クリック
*/
void CWndProcBase::RButton(WPARAM wParam, int x, int y, ENUM_BUTTONTYPE eType)
{
	PostQuitMessage(0);
}


/*! マウス中クリック
*/
void CWndProcBase::MButton(WPARAM wParam, int x, int y, ENUM_BUTTONTYPE eType)
{
	PostQuitMessage(0);
}


/*! 描画
*/
static double dZ = 3.0;

void CWndProcBase::Draw()
{
	wglMakeCurrent(WinDC, hRC);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(dZ < 10.0)
	{
		dZ += 0.1;
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0.0, 0.0, dZ,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0
		);


	/*
	glColor3f(0 , 0 , 1);
	glRectd(-10.5,-10.5,0.5,0.5);
	*/

#if 0
	{
		glBegin(GL_TRIANGLES);
			
		glColor3i(2147483647 , 0 , 0);
		glVertex2f(0 , 0);
		glColor3b(0 , 127 , 0);
		glVertex2f(-1 , -0.9);
		glVertex2f(1 , -0.9);
			
		glEnd();
	}
#endif

#if 1
	{
		//glPushMatrix();
		glRotatef(2 , 0.5 , 1 , 0.25);

		glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA,  GL_ONE_MINUS_SRC_ALPHA);
		glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
		
		glEnable(GL_TEXTURE_2D);

		glAlphaFunc(GL_GEQUAL, 0.5);
		glEnable(GL_ALPHA_TEST);

		//glBindTexture(GL_TEXTURE_2D , g_texID);
		glBindTexture(GL_TEXTURE_2D , m_mapTexId[301]);

		glBegin(GL_POLYGON);
			
		//glColor3ub(0xFF , 0xFF , 0xFF);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glTexCoord2f(0 , 0); 
		//glVertex2f(-0.4 , -0.4);
		glVertex3d(-1.0, -1.0, 0.0);

		//glColor3ub(0xFF , 0xFF , 0xFF);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glTexCoord2f(0 , 1); 
		//glVertex2f(-0.4 , 0.4);
		glVertex3d(-1.0, 1.0, 0.0);
			
		//glColor3ub(0xFF , 0xFF , 0xFF);
		glColor4d(1.0, 1.0, 1.0, 1.0);
		glTexCoord2f(1 , 1); 
		//glVertex2f(0.4 , 0.4);
		glVertex3d(1.0, 1.0, 0.0);
			
		//glColor3ub(0xFF , 0xFF , 0xFF);
		glColor4d(1.0, 0.0, 0.0, 1.0);
		glTexCoord2f(1 , 0); 
		//glVertex2f(0.4 , -0.4);
		glVertex3d(0.5, -0.5, 1.0);
			
		glEnd();

		//glPopMatrix();

		glDisable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GEQUAL, 1.0);
		glDisable(GL_TEXTURE_2D);
	}
#endif

	for(int i=0; i<24; ++i)
	{
		if(dZ > 9.0)
		{
			m_SObject[i].dPosX_2 += ((double)(rand()%100 - 50) / 1000.0); 
			m_SObject[i].dPosY_2 += ((double)(rand()%100 - 50) / 1000.0); 
			m_SObject[i].dPosZ_2 += ((double)(rand()%100 - 50) / 10000.0);

			if(m_SObject[i].dPosX_2 > 1.0 || m_SObject[i].dPosX_2 < -1.0
				|| m_SObject[i].dPosY_2 > 1.0 || m_SObject[i].dPosY_2 < -1.0
				|| m_SObject[i].dPosZ_2 > 1.0 || m_SObject[i].dPosZ_2 < -1.0
				)
			{
				m_SObject[i].dPosX_2 = 0.0; 
				m_SObject[i].dPosY_2 = 0.0; 
				m_SObject[i].dPosZ_2 = 0.0;
			}

			m_SObject[i].dRotZ += ((double)(rand()%100 - 50) / 10.0);
			if(m_SObject[i].dRotZ > 30.0 || m_SObject[i].dRotZ < -30.0)
			{
				m_SObject[i].dRotZ = 0.0;
			}
			
			m_SObject[i].dScaleZ += ((double)(rand()%100 - 50) / 1000.0); 
			if(m_SObject[i].dScaleZ < 0.5 || m_SObject[i].dScaleZ > 3.0)
			{
				m_SObject[i].dScaleZ = 1.0;
			}
		}

		DrawTexture(
			m_SObject[i].dPosX + m_SObject[i].dPosX_2,
			m_SObject[i].dPosY + m_SObject[i].dPosY_2,
			m_SObject[i].dPosZ + m_SObject[i].dPosZ_2,
			m_SObject[i].dRotZ,
			m_SObject[i].dScaleZ,
			m_SObject[i].iIndex
			);
	}


	glFlush();
	SwapBuffers(WinDC);
}


/*! テクスチャ描画
*/
void CWndProcBase::DrawTexture( double dX, double dY, double dZ, double dA, double dE, GLuint iIndex )
{
	//const CLayerWindow::SWindowRect &rect = m_LayerWindow.getWindowRect();

	/*
	glPushMatrix();
	glTranslated(dX, dY, dZ);
	//glRotatef(2 , 0.5 , 1 , 0.25);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
		
	glEnable(GL_TEXTURE_2D);

	glAlphaFunc(GL_GEQUAL, 0.5);
	glEnable(GL_ALPHA_TEST);

	glBegin(GL_POLYGON);
	glBindTexture(GL_TEXTURE_2D , m_mapTexId[iIndex]);

	glColor4d(1.0, 1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); 
	glVertex3d(-1.0, -1.0, 0.0);

	glColor4d(1.0, 1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 1.0); 
	glVertex3d(-1.0, 1.0, 0.0);
			
	glColor4d(1.0, 1.0, 1.0, 1.0);
	glTexCoord2f(1.0, 1.0); 
	glVertex3d(1.0, 1.0, 0.0);
			
	glColor4d(1.0, 1.0, 1.0, 1.0);
	glTexCoord2f(1.0, 0.0); 
	glVertex3d(1.0, -1.0, 0.0);

	glEnd();

	glPopMatrix();
	*/

		
	glPushMatrix();
	glTranslated(dX, dY, dZ);
	//glRotatef(2 , 0.5 , 1 , 0.25);
	glRotatef(dA, 0.0, 0.0, 1.0);
	glScaled(dE, dE, dE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
		
	glEnable(GL_TEXTURE_2D);

	glAlphaFunc(GL_GEQUAL, 0.5);
	glEnable(GL_ALPHA_TEST);

	glBindTexture(GL_TEXTURE_2D , m_mapTexId[iIndex]);

	glBegin(GL_POLYGON);
			
	glColor4d(1.0, 1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); 
	glVertex3d(-1.0, -1.0, 0.0);

	glColor4d(1.0, 1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 1.0); 
	glVertex3d(-1.0, 1.0, 0.0);
			
	glColor4d(1.0, 1.0, 1.0, 1.0);
	glTexCoord2f(1.0, 1.0); 
	glVertex3d(1.0, 1.0, 0.0);
			
	glColor4d(1.0, 1.0, 1.0, 1.0);
	glTexCoord2f(1.0, 0.0); 
	glVertex3d(0.5, -0.5, 0.0);
			
	glEnd();

	glPopMatrix();

	glDisable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GEQUAL, 1.0);
	glDisable(GL_TEXTURE_2D);
}



