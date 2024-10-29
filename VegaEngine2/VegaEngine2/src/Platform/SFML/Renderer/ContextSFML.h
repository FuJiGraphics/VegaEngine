#pragma once

#include "Core/Core.h"
#include "Renderer/RenderContext.h"

namespace fz {

	// forwards
	class Window;

	class ContextSFML : public RenderContext
	{
	public:
		void Init(const ContextData& data = ContextData()) override;
		void SwapBuffers() override;

		ContextData GetContextData() const override;

	private:
		ContextData m_Context;
	};

} // namespace fz