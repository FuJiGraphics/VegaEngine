#include "pch.h"
#include "Sprite.h"

namespace fz {
	Sprite::Sprite(const fz::Sprite& other)
	{
		m_Sprite = other.m_Sprite;
		m_TexPath = other.m_TexPath;
	}

	Sprite::Sprite(const std::string& texPath)
		: m_TexPath(texPath)
	{
		m_Sprite.setTexture(TEXTURE_MGR.Get(texPath));
		m_TexPath = texPath;
	}

	void Sprite::SetTexture(const std::string& texPath)
	{
		m_Sprite.setTexture(TEXTURE_MGR.Get(texPath));
		m_TexPath = texPath;
	}

	void Sprite::SetColor(const sf::Color& color)
	{
		m_Sprite.setColor(color);
	}

	void Sprite::SetOrigins(Origins origins)
	{
		m_Origins = origins;
		if (origins != Origins::Custom)
			Utils::SetOrigin(m_Sprite, origins);
	}

} // namespace fz