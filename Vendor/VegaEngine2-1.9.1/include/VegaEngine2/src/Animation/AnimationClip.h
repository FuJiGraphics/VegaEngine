#pragma once

namespace fz {
	enum class AnimationLoopTypes
	{
		Single,
		Loop,
		PingPong,
	};

	struct AnimationFrame
	{
		Origins origin;
		sf::IntRect texCoord;

		AnimationFrame() = default;
		AnimationFrame(Origins origin, const sf::IntRect& texCoord) 
			: origin(origin)
			, texCoord(texCoord) 
			
		{
			// Default;
		}
	};

	struct AnimationClip
	{
		std::string id;
		AnimationLoopTypes loopType = AnimationLoopTypes::Loop;
		int fps = 30;

		std::vector<AnimationFrame> frames;

		bool loadFromFile(const std::string& filePath);
	};

} // namespace fz
