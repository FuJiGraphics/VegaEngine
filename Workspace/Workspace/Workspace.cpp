#include "Workspace.h"
#include "TestObject.h"

Workspace::Workspace()
	: System(1024, 768, "VegaEngine2")
{
	Super::IsOpen = false;

	Super::PushObject(ObjectGenerator->Take<TestObject>());
}

Workspace::~Workspace()
{

}
