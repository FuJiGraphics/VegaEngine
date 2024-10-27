#pragma once
#include "Utility/Log/Log.h"

extern fz::System* fz::CreateSystem();

int main(int argc, char** argv)
{
	auto app = fz::CreateSystem();
	
	app->Init();
	do {
		app->Run();
		// app->Reset();
	} while (app->IsOpened());
	app->Release();

	return 0;
}