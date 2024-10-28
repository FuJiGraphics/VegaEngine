#pragma once

#include "Core/Core.h"
#include "Renderer/RenderContext.h"

namespace fz {

	// forwards
	class Window;

	class ContextSFML : public RenderContext
	{
	public:
		void Init(Window* window) override;
		void SwapBuffers() override;

	private:

	};

} // namespace fz