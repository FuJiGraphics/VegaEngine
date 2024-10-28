#pragma once

#include "Core/Core.h"

namespace fz {

	// forwards
	class Window;

	class RenderContext
	{
	public:
		virtual void Init(Window* window) = 0;
		virtual void SwapBuffers() = 0;

		static Shared<RenderContext> Create();
	};

} // namespace fz