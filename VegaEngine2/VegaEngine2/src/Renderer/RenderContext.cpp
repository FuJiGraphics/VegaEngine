#include "pch.h"
#include "RenderContext.h"
#include "Platform/SFML/Renderer/ContextSFML.h"

namespace fz {

	Shared<RenderContext> RenderContext::Create()
	{
		return CreateShared<ContextSFML>();
	}

} // namespace fz

