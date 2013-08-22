#ifndef	_WINDOW_h_
#define _WINDOW_h_
#include <windows.h>

#define EntryPoint()	WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpsCmdLine, int nCmdShow)
#define MY_WINDOW_CLASS_NAME "MY_WINDOW_CLASS_NAME"

class Window{
public :
	
	
	Window();
	~Window();
	HWND GethWnd()
	{
		return m_hWnd;
	}
	bool Create(char* title, long x, long y, long width, long height);
	static LRESULT CALLBACK WindowProc(HWND hWnd,UINT uMsg, WPARAM wParam,LPARAM lParam);

private :
	HWND m_hWnd;
};

//#include "Window.cpp"
#endif