#include <VegaEngine2.h>
#include "Editor2D.h"

using namespace std;

class VegaEditor : public fz::System
{
public:
	VegaEditor()
		: System(1024, 768, "VegaEngine2")
	{
		Super::IsOpen = false;
		this->PushLayer(LayerGenerator->Take<Editor2D>("Editor2D"));
	}
	virtual ~VegaEditor()
	{
		// Empty
	}

private:

};

fz::System* fz::CreateSystem()
{
	return new VegaEditor();
}