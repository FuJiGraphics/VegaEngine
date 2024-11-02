#pragma once

namespace fz {

	class Converter
	{
	public:
		static fz::MouseButtonType SfmlToFzType(sf::Mouse::Button button);
	};

} // namespace fz