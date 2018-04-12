#include"Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow)
{
	Application* apps = Application::Instance();
	apps->init(hInstance, 800, 600, "Aladdin");
	MSG msg = apps->GameLoop();
	
	return msg.wParam;
}
