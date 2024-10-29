#include "pch.h"
#include "ContextSFML.h"

namespace fz {

	void ContextSFML::Init(const ContextData& data)
	{
		m_Context.DepthBits = data.DepthBits;
		m_Context.StencilBits = data.StencilBits;
		m_Context.AntialiasingLevel = data.AntialiasingLevel;
		m_Context.MajorVersion = data.MajorVersion;
		m_Context.MinorVersion = data.MinorVersion;
	}

	void ContextSFML::SwapBuffers()
	{

	}

	ContextData ContextSFML::GetContextData() const
	{
		return m_Context;
	}

} // namespace fz 

