#include <VegaEngine2.h>

using namespace std;

class Workspace : public fz::System
{
public:
	Workspace()
		: System(1920, 1080, "VegaEngine2")
	{
		fz::ImGuiManager::SetDocking(false);
	}
	virtual ~Workspace()
	{
		// Empty
	}

private:

};

fz::System* fz::CreateSystem()
{
	return new Workspace();
}

