#define NOMINMAX
#include <windows.h>
#include <process.h>
#include <sstream>

#include "window.h"

#include <d3d9.h>

#pragma comment(lib, "d3d9.lib")

#include "edupt/ppm.h"
#include "edupt/render.h"

#define SCREEN_WIDTH	1280/2
#define SCREEN_HEIGHT	720/2
#define ISFULLSCREENED	0
#define DEFAULT_CLIANT_WIDTH 1280
#define DEFAULT_CLIANT_HEIGHT 720


HINSTANCE g_hInstance;
LPDIRECT3D9 g_pD3D;
LPDIRECT3DDEVICE9 g_pD3DDev;
LPDIRECT3DTEXTURE9 g_tex;

edupt::Color *image;


bool InitDX(HWND hwnd)
{
	g_pD3D=Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D==NULL){
		OutputDebugString("failed -Direct3DCreate9()");
	}

	HRESULT hr;
	D3DDISPLAYMODE d3ddm;
	hr=g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm);
	if(FAILED(hr)){
		OutputDebugString("InitD3D failed -GetAdapterDisplayMode() failed");
		return false;
	}

	//プレゼンテーションパラメータの設定
	D3DPRESENT_PARAMETERS D3DPP;
	ZeroMemory(&D3DPP,sizeof(D3DPRESENT_PARAMETERS));
	D3DPP.BackBufferCount=1;
	if(ISFULLSCREENED){
		D3DPP.Windowed			 = false;
		D3DPP.BackBufferWidth	 = DEFAULT_CLIANT_WIDTH;
		D3DPP.BackBufferHeight	 = DEFAULT_CLIANT_HEIGHT;
	}
	else{
		D3DPP.Windowed=true;
	}
	D3DPP.BackBufferFormat		 = d3ddm.Format;
	D3DPP.SwapEffect			 = D3DSWAPEFFECT_DISCARD;
	D3DPP.EnableAutoDepthStencil = true;
	D3DPP.AutoDepthStencilFormat = D3DFMT_D16;
	D3DPP.Flags					 = true;
	D3DPP.PresentationInterval	 = D3DPRESENT_INTERVAL_ONE;
   
//デバイスオブジェクトの作成
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&D3DPP,&g_pD3DDev))){
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&D3DPP,&g_pD3DDev))){
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_REF,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&D3DPP,&g_pD3DDev))){
				OutputDebugString("InitD3D failed -デバイスオブジェクトの作成に失敗 \n");
				return false;
			}
		}
	}

	g_pD3DDev->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 1,D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&g_tex, NULL);

	return true;
}

void Init(HWND hwnd)
{
	// 初期化

	// DX9
	InitDX(hwnd);
}

void Run()
{
	// シーンの作成
	edupt::render(SCREEN_WIDTH, SCREEN_HEIGHT, 64, 2, image);
}

// シーンのファイル出力
void ExportScene(void* data)
{
	DWORD time,lasttime;
	lasttime = timeGetTime();
	time = lasttime;
	int minute = 0;
	while(true)
	{
		time = timeGetTime();
		if(time-lasttime >= 1000*60)
		{
			minute++;
			std::string filename = "../etc/image_min";
			std::ostringstream stream;
			stream << minute;
			filename += stream.str();
			filename += ".ppm";
			save_ppm_file(filename, image, SCREEN_WIDTH, SCREEN_HEIGHT);
			lasttime = time;
		}
		Sleep(100);
	}
}

// シーンの描画
void DrawScene(void* data)
{
#if 1
	struct vertex 
	{
	    FLOAT x, y, z, rhw;
		FLOAT tu, tv;
	};
	vertex v[4] = 
	{
		{0,                        0, 0.0f, 1.0f, 0.0f, 0.0f},
		{SCREEN_WIDTH,             0, 0.0f, 1.0f, 1.0f, 0.0f},
		{0,            SCREEN_HEIGHT, 0.0f, 1.0f, 0.0f, 1.0f},
		{SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 1.0f, 1.0f, 1.0f},
	};

	D3DLOCKED_RECT pRect;
	DWORD time,lasttime;
	lasttime = timeGetTime();
	time = lasttime;

	while(true)
	{
		time = timeGetTime();
		if(time-lasttime >= 1000*10)
		{
			g_tex->LockRect(0, &pRect, NULL, D3DLOCK_DISCARD);
			for(int y = 0; y<SCREEN_HEIGHT; y++)
			{
				for(int x = 0; x<SCREEN_WIDTH; x++)
				{
					DWORD color = 0x00ff00ff;
					color = (edupt::to_int(image[y*SCREEN_WIDTH+x].x_)<<16) + (edupt::to_int(image[y*SCREEN_WIDTH+x].y_)<<8) + edupt::to_int(image[y*SCREEN_WIDTH+x].z_);
					memcpy((BYTE*)pRect.pBits+pRect.Pitch*y + 4*x, &color, sizeof(DWORD));
				}
			}
			g_tex->UnlockRect(0);
			lasttime = time;
		}

		g_pD3DDev->BeginScene();
		g_pD3DDev->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_RGBA(128,128,128,0),1.0f,0);

		g_pD3DDev->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

		g_pD3DDev->SetTexture(0, g_tex);
		g_pD3DDev->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(vertex));

		g_pD3DDev->EndScene();
		g_pD3DDev->Present(NULL, NULL, NULL, NULL);
	}
#endif
}

// プロシージャ
void WindowProc(void* data)
{
	MSG msg;
	while(true)
	{
		if(PeekMessage(&msg,NULL, 0, 0,PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				DispatchMessage(&msg);
			}
		}
		else
		{
			Sleep(1);
		}
	}
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	MSG msg;
	HANDLE	hMutex; //ミューテックスのハンドル
	HANDLE hThreadExport, hThreadWindow, hThreadDraw;
	Window win;
	win.Create("preview",0,0,SCREEN_WIDTH+30,SCREEN_HEIGHT+80);

	image = new edupt::Color[SCREEN_WIDTH * SCREEN_HEIGHT];

	Init(win.GethWnd());

	hMutex = CreateMutex(NULL, FALSE, NULL);
	hThreadExport = (HANDLE)_beginthread(ExportScene,0,NULL);	//レンダリング経過出力スレッド
	hThreadWindow = (HANDLE)_beginthread(WindowProc,0,NULL);	//プロシージャ
	hThreadDraw = (HANDLE)_beginthread(DrawScene,0,NULL);	//プレビュー描画スレッド

	Run();
	CloseHandle(hThreadExport);
	CloseHandle(hThreadWindow);
	CloseHandle(hThreadDraw);
	CloseHandle(hMutex);

	while(true)
	{
		if(PeekMessage(&msg,NULL, 0, 0,PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				DispatchMessage(&msg);
			}
		}
		else
		{
			Sleep(1);
		}
	}

	delete(image);

	return 0;
}
