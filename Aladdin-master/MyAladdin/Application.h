#pragma once
#ifndef __APPLICATION_H__
#define __APPLICATION_H__
#include<Windows.h>
#include"SenceManager.h"
class Application
{
private:
	char*		_title;
	int			_width;
	int			_height;
	int			_Fps;
	HINSTANCE	_hInstance;
	HWND		_hwnd;
	static Application*			__instance;
	Application();
public:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static Application*			Instance();
	void						init(HINSTANCE hInstance, int width, int height, char* title);
	MSG							GameLoop();
	//Get and set properties
	int							getWidth();
	void						setWidth(int width);
	int							getHeight();
	void						setHeight(int height);
	int							getFps();
	void						setFps(int fps);
	HINSTANCE					gethInstance();
	void						sethInstance(HINSTANCE hInstance);
	HWND						getHWND();
	void						setHWND(HWND hwnd);
	~Application();
};

#endif __APPLICATION_H__