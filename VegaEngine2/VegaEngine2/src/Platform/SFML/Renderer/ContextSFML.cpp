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

	void ContextSFML::SetViewport(int x, int y, int w, int h)
	{
		glViewport(x, y, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
	}

	ContextData ContextSFML::GetContextData() const
	{
		return m_Context;
	}

} // namespace fz 

