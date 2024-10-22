#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "Core/System.h"

namespace fz {
	namespace _internal {
		class App
		{
		public:
			App(int w, int h, const char* title)
				: w(w), h(h)
				, title(title)
			{ }
			void Create()
			{
				auto& system = System::GetInstance();
				system.Init({ w, h, title });
			}
			void Run()
			{
				auto& system = System::GetInstance();
				system.Run();
			}
			void Reset()
			{
				auto& system = System::GetInstance();
				system.Reset();
			}
			void Delete()
			{
				auto& system = System::GetInstance();
				system.Reset();
			}
			bool IsReset()
			{
				auto& system = System::GetInstance();
				return (system.IsReset());
			}

		private:
			int	w, h;
			std::string title;
		};
	}
}

using namespace fz;

static void BeginProcess()
{
	WindowInfo& info = CreateApplication();
	fz::_internal::App app(info.Width, info.Height, info.Title.c_str());
	app.Create();
	do {
		app.Reset();
		Runtime();
		app.Run();
	} while (app.IsReset());

	app.Reset();
}