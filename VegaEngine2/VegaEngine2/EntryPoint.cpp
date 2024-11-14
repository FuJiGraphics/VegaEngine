#include "pch.h"
#include "EntryPoint.h"

int main(int argc, char** argv)
{
	auto app = fz::CreateSystem();

	app->Init();
	do {
		app->Run();
		// app->Reset();
	} while (app->IsOpened());
	app->Release();
	
	delete app;
	return 0;
}