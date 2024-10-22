#pragma once

// standards
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <functional>
#include <thread>

// graphics
#include <SFML/Graphics.hpp>

namespace fz {

	template <typename T>
	using MemoryPool = std::unordered_map<std::string, T>;

} // namespace fz
