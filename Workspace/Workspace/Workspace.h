#pragma once
#include <VegaEngine2.h>

using namespace std;

class Workspace : public fz::System
{
public:
	Workspace();
	virtual ~Workspace();

private:

};

fz::System* fz::CreateSystem()
{
	return new Workspace();
}