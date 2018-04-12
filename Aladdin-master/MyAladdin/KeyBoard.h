#pragma once
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__
#include"Global.h"

//Lớp thư viện quản lý việc xử lý bàn phím
class KeyBoard
{
private:
	KeyBoard();
	static KeyBoard*			__instance;
	char						_keyStates[256];
	char						_preKeyStates[256];
	LPDIRECTINPUT8				_dinput;
	LPDIRECTINPUTDEVICE8		_ddevice;
	DIDEVICEOBJECTDATA			_keyEvents[GL_KEY_BUFFER_SIZE];		// Buffered keyboard data
public:
	~KeyBoard();
	static KeyBoard*			Instance();

	HRESULT						acquire();
	HRESULT						unacquire();
	LPDIRECTINPUTDEVICE8		getDevice();
	DIDEVICEOBJECTDATA*			getEvents();
	char*						getKeyState();

	//Cho phép nhấn và giữ
	bool						isKeyPress(int keyCode);
	//Chỉ cho phép nhấn 1 lần và không được giữ
	bool						isKeyDown(int keyCode);
	bool						isKeyUp(int keyCode);
	bool						isKeyRelease(int keyCode);
	
	void						update();
private:
	bool						initialize();
	bool						isPressCurrentFrame(int keyCode);
	bool						isPressPreviousFrame(int keyCode);
	int							temp = 0;
};

#endif __KEYBOARD_H__