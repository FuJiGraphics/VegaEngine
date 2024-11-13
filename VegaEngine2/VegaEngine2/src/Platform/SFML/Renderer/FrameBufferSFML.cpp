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

	void FrameBufferSFML::Resize(unsigned int width, unsigned int height)
	{
		if (m_Spec.Width != width || m_Spec.Height != height)
		{
			m_Spec.Width = width;
			m_Spec.Height = height;
			sf::Texture oldTexture = m_Buffer.getTexture();

			// ���ο� ũ��� RenderTexture ����
			m_Buffer.create(width, height);

			// RenderTexture �ʱ�ȭ
			m_Buffer.clear(sf::Color::Transparent);

			// ���� ������ RenderTexture�� ���� �ؽ�ó�� ������ ����
			sf::Sprite sprite(oldTexture);
			m_Buffer.draw(sprite);
			m_Buffer.display();
		}
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