#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include "ResourceManager_internal.h"

namespace fz {

	template <typename T>
	class ResourceManager
	{
	public:
		static bool		Load(const std::string& path);
		static bool		Unload(const std::string& path);
		static void		UnloadAll();
		static T&		Get_Safety(const std::string& path);
		static T&		Get(const std::string& path);
	};

	using Texture = ResourceManager<sf::Texture>;
	using Font = ResourceManager<sf::Font>;

} // namespace fz;

#include "ResourceManager.hpp"