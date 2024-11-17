#pragma once

namespace fz {

	class Converter
	{
	public:
		static fz::MouseButtonType SfmlToFzType(sf::Mouse::Button button);
		static std::string ToString(Origins origin);
		static Origins StringToOrigins(const std::string& str);
	};

} // namespace fz