#include "Global.h"
#include <iostream>
#include <fstream>

bool						Global::isGameRunning = true;

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

Global::Global()
{
}


Global::~Global()
{
}



void Global::GLPostMessage(char * msg)
{
	MessageBox(NULL, msg, "Notify", MB_OK | MB_ICONINFORMATION);
}

void Global::GLPostMessage(const LPCSTR s, ...)
{
	char buff[1024];
	int length = strlen(s);

	va_list ap;
	va_start(ap, s);
	_vsnprintf_s(buff, sizeof(buff), s, ap); //sizeof(szBuff)
	va_end(ap);

	MessageBox(NULL, buff, "Notify", MB_OK | MB_ICONINFORMATION);
}
