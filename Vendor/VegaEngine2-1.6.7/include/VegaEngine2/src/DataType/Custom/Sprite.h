#pragma once

namespace fz {

	class Sprite
	{
	public:
		Sprite() = default;
		Sprite(const fz::Sprite& other);
		Sprite(const std::string& texPath);

		void SetTexture(const std::string& texPath);
		void SetColor(const sf::Color& color);

		std::string GetTexturePath() const { return m_TexPath; }

		operator sf::Sprite& () { return m_Sprite; }
		operator const sf::Sprite& () const { return m_Sprite; }

	private:
		sf::Sprite m_Sprite;
		std::string m_TexPath;
	};

} // namespace fz