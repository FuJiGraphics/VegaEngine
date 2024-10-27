#include "Workspace.h"

Workspace::Workspace()
	: System(1024, 768, "VegaEngine2")
{
	Super::IsOpen = false;

}

Workspace::~Workspace()
{

}
