#include <Windows.h>
#include <ctime>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "engine\app\WinApp.h"
#include "game\states\MainMenuState.h"

#define GAME_WIDTH	1024
#define GAME_HEIGHT	768

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Application entry point
Parameters:
[in] hInstance - Application instance
[in] hPrevInstance - Junk
[in] lpCmdLine - Command line arguments
[in] nCmdShow - Window display flags
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	srand(unsigned int(time(0)));

	WinApp app;
#if _DEBUG
	app.Initialize(L"Hidden Armada - Debug", hInstance, new MainMenuState(), GAME_WIDTH, GAME_HEIGHT);
#else
	app.Initialize(L"Hidden Armada", hInstance, new MainMenuState(), GAME_WIDTH, GAME_HEIGHT);
#endif

	app.Run();
	app.Release();

	return 0;
}