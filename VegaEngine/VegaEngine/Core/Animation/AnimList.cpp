#include "Core/stdafx.h"
#include "AnimList.h"

namespace fz {
	
	AnimList::AnimList(const std::string& name)
		: m_Name(name)
	{
		// Empty
	}

	AnimList::~AnimList()
	{
		// Empty
	}

	void AnimList::Insert(const std::string& name, sf::Sprite& target)
	{
		m_AnimList.insert(std::make_pair(name, fz::Anim(target)));
	}

	Anim& AnimList::GetAnim(const std::string& name)
	{
		return m_AnimList.at(name);
	}

	void AnimList::Update(float dt)
	{
		for (auto& anim : m_AnimList)
		{
			if (anim.second.Activated)
				anim.second.Update(dt);
		}
	}

	void AnimList::Draw(Camera& camera)
	{
		for (auto& anim : m_AnimList)
		{
			if (anim.second.Activated)
				anim.second.Draw(camera);
		}
	}

	void AnimList::SetActivated(bool enabled, const std::string& name)
	{
		m_AnimList.at(name).Activated = enabled;
		for (auto& anim : m_AnimList)
		{
			if (anim.first != name)
			{
				anim.second.Activated = false;
			}
		}
	}

	void AnimList::SetActivatedAll(bool enabled)
	{
		for (auto& anim : m_AnimList)
		{
			anim.second.Activated = enabled;
		}
	}

	void AnimList::SetRepeatAll(bool enabled)
	{
		for (auto& anim : m_AnimList)
		{
			anim.second.Repeat = enabled;
		}
	}

	Anim& AnimList::operator[](const std::string& name)
	{
		return m_AnimList.at(name);
	}

} // namespace fz
