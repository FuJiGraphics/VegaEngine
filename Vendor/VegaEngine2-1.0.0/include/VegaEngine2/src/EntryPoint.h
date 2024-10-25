#pragma once

extern fz::System* fz::CreateSystem();

int main(int argc, char** argv)
{
	auto app = fz::CreateSystem();

	std::cout << "Create System!" << std::endl;
	app->Init();
	do {
		app->Run();
		app->Reset();
	} while (app->IsOpened());
	app->Release();

	return 0;
}