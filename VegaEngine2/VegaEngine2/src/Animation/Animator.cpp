#include "pch.h"
#include "Animator.h"

namespace fz {

	void Animator::AddEvent(const std::string& id, int frame, std::function<void()> action)
	{
		auto key = std::pair<std::string, int>(id, frame);
		auto it = events.find(key);
		if (it == events.end())
		{
			events.insert({ key, {id, frame} });
		}
		events[key].actions.push_back(action);
	}

	void Animator::Update(float dt)
	{
		if (!isPlaying)
			return;

		accumTime += dt * std::fabs(speed);
		if (accumTime < frameDuration)
			return;

		currentFrame += speed > 0.f ? 1 : -1;
		accumTime = 0.f;

		if (currentFrame == checkFrame)
		{
			if (!playeQueue.empty())
			{
				std::string clipId = playeQueue.front();
				Play(clipId, false);
				playeQueue.pop();
				return;
			}

			switch (currentClip->loopType)
			{
				case AnimationLoopTypes::Single:
					currentFrame = speed > 0.f ? totalFrame - 1 : 0;
					break;
				case AnimationLoopTypes::Loop:
					currentFrame = speed > 0.f ? 0 : totalFrame - 1;
					break;
				case AnimationLoopTypes::PingPong:
					if (speed > 0.f)
					{
						currentFrame = totalFrame - 2;
						checkFrame = -1;
						speed *= -1.0f;
					}
					else
					{
						currentFrame = 1;
						checkFrame = totalFrame;
						speed *= -1.0f;
					}
					break;
			}
		}

		SetFrame(currentClip->frames[currentFrame]);
		auto find = events.find({ currentClip->id, currentFrame });
		if (find != events.end())
		{
			auto& ev = find->second;
			for (auto& action : ev.actions)
			{
				if (action)
				{
					action();
				}
			}
		}
	}

	void Animator::Play(const std::string& clipId, bool clearQueue)
	{
		Play(&ANI_CLIP_MGR.Get(clipId), clearQueue);
	}

	void Animator::Play(AnimationClip* clip, bool clearQueue)
	{
		if (currentClip == clip)
			return;
		else
			this->Stop();

		if (clearQueue)
		{
			while (!playeQueue.empty())
			{
				playeQueue.pop();
			}
		}

		isPlaying = true;

		currentClip = clip;
		totalFrame = clip->frames.size();
		checkFrame = this->speed > 0.f ? totalFrame : -1;
		currentFrame = speed > 0.f ? 0 : totalFrame - 1;

		frameDuration = 1.f / clip->fps;
		accumTime = 0.f;
		SetFrame(currentClip->frames[currentFrame]);
	}

	void Animator::PlayQueue(const std::string& clipId)
	{
		playeQueue.push(clipId);
	}

	void Animator::Stop()
	{
		isPlaying = false;
		currentFrame = 0;
		checkFrame = totalFrame - 1;
	}

	void Animator::SetFrame(const AnimationFrame& frame)
	{
		if (sprite == nullptr || transformComp == nullptr)
			return;

		*sprite = frame.sprite;
		transformComp->AnimTransform = currentClip->transform;
	}

} // namespace fz