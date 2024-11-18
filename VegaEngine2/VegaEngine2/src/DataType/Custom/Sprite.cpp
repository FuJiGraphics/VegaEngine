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

	void Sprite::SetTextureWithMask(const std::string& texPath, const sf::Color& alphaMask)
	{
		m_IsMaskMode = true;
		sf::Image image;
		image.loadFromFile(texPath);
		image.createMaskFromColor(alphaMask);
		static sf::Texture texture;
		texture.create(image.getSize().x, image.getSize().y);
		texture.loadFromImage(image);
		m_Sprite.setTexture(texture);
		m_Sprite.setTextureRect({ 0, 0, (int)texture.getSize().x, (int)texture.getSize().y });
		m_TexPath = texPath;
		m_Mask = alphaMask;
	}

	void Sprite::SetTexture(const std::string& texPath)
	{
		const sf::Texture& texture = TEXTURE_MGR.Get(texPath);
		m_Sprite.setTexture(texture);
		m_Sprite.setTextureRect({ 0, 0, (int)texture.getSize().x, (int)texture.getSize().y });
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

	void Sprite::SetMaskColor(bool enabled, const sf::Color& alphaMask)
	{
		m_IsMaskMode = enabled;
		m_Mask = alphaMask;
		if (m_IsMaskMode)
			this->SetTextureWithMask(m_TexPath, m_Mask);
		else
			this->SetTexture(m_TexPath);
	}

} // namespace fz