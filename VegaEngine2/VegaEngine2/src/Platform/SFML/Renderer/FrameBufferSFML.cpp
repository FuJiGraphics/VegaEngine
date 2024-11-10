#include "pch.h"
#include "FrameBufferSFML.h"

namespace fz {

	FrameBufferSFML::FrameBufferSFML(const FramebufferSpec& specification)
		: m_Spec(specification)
		, m_Buffer()
	{
		sf::ContextSettings setting;
		setting.antialiasingLevel = specification.MultisampleLevel;
		m_Buffer.create(specification.Width, specification.Height, setting);
	}

	FramebufferSpec FrameBufferSFML::GetInfo() const
	{
		return { m_Spec.Width, m_Spec.Height, m_Spec.MultisampleLevel, m_Spec.SwapChainTarget };
	}

	sf::RenderTexture& FrameBufferSFML::GetBuffer()
	{
		return m_Buffer;
	}

	void FrameBufferSFML::Clear()
	{
		m_Buffer.clear({ 100, 100, 100 });
	}

	FrameBufferSFML::operator sf::RenderTexture& ()
	{
		return m_Buffer;
	}

	FrameBufferSFML::operator const sf::RenderTexture& () const
	{
		return m_Buffer;
	}

} // namespace fz