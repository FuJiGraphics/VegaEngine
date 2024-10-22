#pragma once

#include "Defines.h"
#include "Framework/GameObject.h"
#include <list>
#include <SFML/Graphics.hpp>


class Scene
{
protected:
	SceneIDs id;
	std::list<GameObject*> objects;

public:
	Scene(SceneIDs id);
	virtual ~Scene() = default;

	virtual void Init();
	virtual void Release();

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void Draw(sf::RenderWindow& window);

	template<typename T>
	T* AddGo(T* obj);

	virtual void RemoveGo(GameObject* obj);
	virtual GameObject* FindGo(const std::string& name);

	/*
	* @brief 게임 오브젝트 찾기
	* @param[in]	name: 찾을 오브젝트의 이름
	* @param[out]	list: 찾은 오브젝트를 담아줄 수 있는 버퍼
	* @return int: 찾은 오브젝트의 개수 (같은 이름 포함)
	*/
	virtual int FindGoAll(const std::string& name, std::list<GameObject*>& list);
};

template<typename T>
inline T* Scene::AddGo(T* obj)
{
	auto iter = std::find_if(objects.begin(), objects.end(),
		[obj](GameObject* element)
		{
			return (obj == element);
		});
	if (iter == objects.end())
	{
		objects.push_back(obj);
	}
	return (obj);
}
