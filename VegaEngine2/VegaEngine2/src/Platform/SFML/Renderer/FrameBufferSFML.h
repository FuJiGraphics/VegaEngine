#pragma once

#include "Renderer/FrameBuffer.h"

namespace fz {

	class FrameBufferSFML : public Framebuffer
	{
	public:
		FrameBufferSFML(const FramebufferSpec& specification);

		FramebufferSpec GetInfo() const override;
		sf::RenderTexture& GetBuffer() override;
		void Clear() override;

		operator sf::RenderTexture& () override;
		operator const sf::RenderTexture& () const override;

	private:
		FramebufferSpec m_Spec;
		sf::RenderTexture m_Buffer;
	};

} // namespace fz