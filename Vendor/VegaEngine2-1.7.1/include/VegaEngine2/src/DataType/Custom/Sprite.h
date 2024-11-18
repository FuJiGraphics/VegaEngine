#pragma once

namespace fz {

	class Sprite
	{
	public:
		Sprite() = default;
		Sprite(const fz::Sprite& other);
		Sprite(const std::string& texPath);

		void SetTextureWithMask(const std::string& texPath, const sf::Color& alphaMask);
		void SetTexture(const std::string& texPath);
		void SetColor(const sf::Color& color);
		void SetOrigins(Origins origins);
		void SetMaskColor(bool enabled, const sf::Color& alphaMask);

		bool IsMaskMode() const { return m_IsMaskMode; }
		sf::Color GetMaskColor() const { return m_Mask; }
		sf::Color GetColor() const { return m_Sprite.getColor(); }
		Origins GetOrigins() const { return m_Origins; }
		std::string GetTexturePath() const { return m_TexPath; }

		operator sf::Sprite& () { return m_Sprite; }
		operator const sf::Sprite& () const { return m_Sprite; }

	private:
		sf::Sprite	m_Sprite;
		std::string	m_TexPath;
		Origins		m_Origins;
		sf::Color	m_Mask;
		bool		m_IsMaskMode = false;
	};

} // namespace fz