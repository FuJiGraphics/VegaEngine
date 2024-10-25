#pragma once
#include "Utility/Log/Log.h"

extern fz::System* fz::CreateSystem();

int main(int argc, char** argv)
{
	auto app = fz::CreateSystem();
	
	fz::Log.Trace("asd {0} {1} {2}", 1.1, 3, "asd");
	fz::Log.Debug("asd {0} {1} {2}", 1.1, 3, "asd");
	fz::Log.Error("asd {0} {1} {2}", 1.1, 3, "asd");
	fz::Log.Info("asd {0} {1} {2}", 1.1, 3, "asd");
	fz::Log.Warn("asd {0} {1} {2}", 1.1, 3, "asd");
	fz::Log.Critical("asd {0} {1} {2}", 1.1, 3, "asd");
	app->Init();
	do {
		app->Run();
		app->Reset();
	} while (app->IsOpened());
	app->Release();

	return 0;
}