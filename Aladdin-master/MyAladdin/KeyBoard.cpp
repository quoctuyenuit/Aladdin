#include "KeyBoard.h"
#include"Application.h"
KeyBoard*				KeyBoard::__instance = NULL;

KeyBoard * KeyBoard::Instance()
{
	if (!__instance)
		KeyBoard::__instance = new KeyBoard();
	return KeyBoard::__instance;
}

KeyBoard::KeyBoard()
{
	if(!this->initialize())
		Global::GLPostMessage("[Error] Can't create Keyboard device");
}

KeyBoard::~KeyBoard()
{
	if (_dinput)
		this->_dinput->Release();
	if (_ddevice)
		_ddevice->Release();
}

bool KeyBoard::initialize()
{
	Application* apps = Application::Instance();

	HRESULT result;
	result = DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&_dinput,
		NULL);

	if (result != DI_OK)
	{
		return false;
	}

	result = _dinput->CreateDevice(
		GUID_SysKeyboard,
		&_ddevice,
		NULL);

	if (result != DI_OK)
	{
		Global::GLPostMessage("[Error] Can't create Keyboard device");
		return false;
	}
	

	result = _ddevice->SetDataFormat(&c_dfDIKeyboard);
	if (result != DI_OK)
	{
		return false;
	}

	result = _ddevice->SetCooperativeLevel(apps->getHWND(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	if (result != DI_OK)
	{
		return false;
	}

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = GL_KEY_BUFFER_SIZE; // Arbitrary buffer size


	result = _ddevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (result != DI_OK) 
		return false;

	return true;
}

HRESULT KeyBoard::acquire()
{
	return _ddevice->Acquire();
}

HRESULT KeyBoard::unacquire()
{
	return _ddevice->Unacquire();
}

LPDIRECTINPUTDEVICE8 KeyBoard::getDevice()
{
	return _ddevice;
}

DIDEVICEOBJECTDATA * KeyBoard::getEvents()
{
	acquire();
	DWORD dwElements = GL_KEY_BUFFER_SIZE;
	HRESULT hr = getDevice()->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _keyEvents, &dwElements, 0);
	return this->_keyEvents;
}

char * KeyBoard::getKeyState()
{
	return this->_keyStates;
}
//==============================================================
//Main method
//==============================================================
void KeyBoard::update()
{
	//Save keyboard old state
	for (auto i = 0; i < 256; i++)
		this->_preKeyStates[i] = this->_keyStates[i];

	//update keyboard new state
	acquire();
	_ddevice->GetDeviceState(sizeof(_keyStates), (LPVOID)&_keyStates);
}

bool KeyBoard::isPressCurrentFrame(int keyCode)
{
	return (this->_keyStates[keyCode] & 0x80) > 0;
}

bool KeyBoard::isPressPreviousFrame(int keyCode)
{
	return (this->_preKeyStates[keyCode] & 0x80) > 0;
}

bool KeyBoard::isKeyPress(int keyCode)
{
	return this->isPressCurrentFrame(keyCode);
}

bool KeyBoard::isKeyDown(int keyCode)
{
	/*return (((_keyStates[keyCode] & 0x80) > 0) &&
	!(this->_preKeyStates[keyCode] & 0x80) > 0);*/

	return this->isPressCurrentFrame(keyCode) &&
		!this->isPressPreviousFrame(keyCode);
}

bool KeyBoard::isKeyUp(int keyCode)
{
	return !this->isPressCurrentFrame(keyCode) &&
		this->isPressPreviousFrame(keyCode);
}

bool KeyBoard::isKeyRelease(int keyCode)
{
	return !this->isPressCurrentFrame(keyCode) &&
		!this->isPressPreviousFrame(keyCode);
}