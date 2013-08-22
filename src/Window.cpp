#include "Window.h"

LRESULT CALLBACK Window::WindowProc(HWND hWnd,UINT uMsg, WPARAM wParam,LPARAM lParam){
	
	switch(uMsg){
		
		case WM_KEYDOWN:
			//終了処理
			if(wParam==VK_ESCAPE){
				PostQuitMessage(0);
			}
		return 0;
		case WM_SETCURSOR: // カーソルの設定
            SetCursor(NULL);
            break;
		case WM_CREATE:
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		return 0;
	}
	return DefWindowProc(hWnd, uMsg,wParam, lParam);
}
Window::Window()
{
	m_hWnd = NULL;
	
}
Window::~Window()
{
	
}

bool Window::Create(char* title, long x, long y, long width, long height )
{
	HINSTANCE hInst = GetModuleHandle(NULL);

	WNDCLASSEX wcex;
	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_VREDRAW | CS_HREDRAW;
	wcex.lpfnWndProc	= WindowProc;
	wcex.hInstance		= GetModuleHandle(NULL);
	wcex.hIcon			= (HICON)LoadImage(NULL,MAKEINTRESOURCE(IDI_APPLICATION),IMAGE_ICON,0,0,LR_DEFAULTSIZE | LR_SHARED);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= MY_WINDOW_CLASS_NAME;
	wcex.hIconSm		= (HICON)LoadImage(NULL,MAKEINTRESOURCE(IDI_APPLICATION),IMAGE_ICON,0,0,LR_DEFAULTSIZE | LR_SHARED);
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;

	if(!RegisterClassEx(&wcex))
	{
		OutputDebugString("Window::Create() is failed. - RegisterClassEx() return false.");
		return false;
	}
	

	m_hWnd=CreateWindow(MY_WINDOW_CLASS_NAME,title,WS_VISIBLE,x,y,width,height,NULL,NULL,hInst,NULL);
	ShowWindow(m_hWnd,SW_SHOWDEFAULT);
	UpdateWindow(m_hWnd);
	return true;
}