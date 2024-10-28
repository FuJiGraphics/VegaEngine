#include "pch.h"
#include "ContextSFML.h"

namespace fz {

	void ContextSFML::Init(Window* window)
	{
		unsigned int depthBits = 24;
		unsigned int stencilBits = 8;
		unsigned int antialias = 2;
		window->SetContext(depthBits, stencilBits, antialias);
	}

	void ContextSFML::SwapBuffers()
	{

	}

} // namespace fz 

