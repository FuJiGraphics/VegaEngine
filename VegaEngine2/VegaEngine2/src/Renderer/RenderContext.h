#pragma once

#include "Core/Core.h"

namespace fz {

	struct ContextData
	{
		unsigned int DepthBits = 24;
		unsigned int StencilBits = 8;
		unsigned int AntialiasingLevel = 4;
		unsigned int MajorVersion = 3;
		unsigned int MinorVersion = 0;
	};

	class RenderContext
	{
	public:
		virtual void Init(const ContextData& data = ContextData()) = 0;
		virtual void SwapBuffers() = 0;

		virtual ContextData GetContextData() const = 0;

		static Shared<RenderContext> Create();
	};

} // namespace fz