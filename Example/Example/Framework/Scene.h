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
	* @brief ���� ������Ʈ ã��
	* @param[in]	name: ã�� ������Ʈ�� �̸�
	* @param[out]	list: ã�� ������Ʈ�� ����� �� �ִ� ����
	* @return int: ã�� ������Ʈ�� ���� (���� �̸� ����)
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