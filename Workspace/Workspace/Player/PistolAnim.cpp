#include "PistolAnim.h"

namespace fz {

	void PistolStatusManager::Init()
	{
		S_PistolKeyMap.insert({ KeyType::A, PistolStatus::Move });
		S_PistolKeyMap.insert({ KeyType::D, PistolStatus::Move });
	}

	void PistolStatusManager::Update(float dt)
	{
		if (Input::IsKeyPressed(KeyType::A) || Input::IsKeyPressed(KeyType::D))
		{
			auto& list = s_StatusMap[PistolStatus::Move];
			for (auto& clip : list)
			{
				s_Animator.SetTarget(clip.Sprite);
				s_Animator.SetSpeed(clip.Speed);
				s_Animator.Play(&*clip.Clip);
			}
		}
	}

	void PistolStatusManager::AttachAnimClip(PistolStatus status, sf::Sprite* sprite, Shared<AnimationClip>& clip, float speed)
	{
		s_StatusMap[status].push_back({ sprite, clip, speed });
	}

} // namespace fz
