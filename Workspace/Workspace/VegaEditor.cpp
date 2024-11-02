#include <VegaEngine2.h>
#include "TestLayer.h"

using namespace std;

class Workspace : public fz::System
{
public:
	Workspace()
		: System(1024, 768, "VegaEngine2")
	{
		Super::IsOpen = false;
		this->PushLayer(LayerGenerator->Take<TestLayer>("Editor2D"));
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