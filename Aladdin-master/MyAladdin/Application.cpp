#include "Application.h"
#include"Global.h"
#include "Game.h"
#include<Windows.h>
Application*			Application::__instance = NULL;

Application::Application()
{
	this->_Fps = 60;
}

LRESULT Application::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Global::isGameRunning = false;
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN:

		break;

	case WM_KEYDOWN:
		break;

	case WM_KEYUP:
		SenceManager::Instance()->GetCurrentSence()->OnKeyUp(wParam);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return LRESULT();
}

Application * Application::Instance()
{
	if (!__instance)
		__instance = new Application();
	return __instance;
}

void Application::init(HINSTANCE hInstance, int width, int height, char* title)
{
	this->_hInstance = hInstance;
	this->_width = width;
	this->_height = height;
	this->_title = title;

	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = NULL;
	wndclass.hIconSm = NULL;
	wndclass.hInstance = _hInstance;
	wndclass.lpfnWndProc = (WNDPROC)WndProc;
	wndclass.lpszClassName = this->_title;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndclass);

	_hwnd = CreateWindow(
		this->_title,
		this->_title,
		WS_OVERLAPPEDWINDOW,//WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_DLGFRAME,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		_width,
		_height,
		NULL,
		NULL,
		_hInstance,
		NULL);

	if (!_hwnd)
	{
		Global::GLPostMessage("[Error] Can't Initializing windows");
		return;
	}
	ShowWindow(_hwnd, SW_SHOWNORMAL);
	UpdateWindow(_hwnd);
}

MSG Application::GameLoop()
{
	MSG msg;
	Game game;
	game.Initialize();

	float tickPerFrame = 1.0f / _Fps, delta = 0;

	while (Global::isGameRunning)
	{
		Timer::Instance()->StartCounter();
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		delta += Timer::Instance()->GetCouter();

		if (delta >= tickPerFrame)
		{
			game.Run(delta);
			delta = 0;
		}
		else
		{
			Sleep((tickPerFrame - delta)*10);
			delta = tickPerFrame;
		}
	}
	return msg;
}

int Application::getWidth()
{
	return _width;
}

void Application::setWidth(int width)
{
	this->_width = width;
}

int Application::getHeight()
{
	return _height;
}

void Application::setHeight(int height)
{
	this->_height = height;
}

int Application::getFps()
{
	return this->_Fps;
}

void Application::setFps(int fps)
{
	this->_Fps = fps;
}

HINSTANCE Application::gethInstance()
{
	return _hInstance;
}

void Application::sethInstance(HINSTANCE hInstance)
{
	this->_hInstance = hInstance;
}

HWND Application::getHWND()
{
	return this->_hwnd;
}

void Application::setHWND(HWND hwnd)
{
	this->_hwnd = hwnd;
}

Application::~Application()
{
}
