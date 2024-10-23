#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "Core/System.h"

using namespace fz;

WindowInfo CreateApplication();
void Runtime(System& system);

static void BeginProcess()
{
	WindowInfo& info = CreateApplication();
	System* app = new System();
	do {
		app->Release();
		app->Create(info.Width, info.Height, info.Title.c_str());
		Runtime(*app);
		app->Run();
	} while (!app->IsClosed());

	app->Release();
	delete app;
	app = nullptr;
}