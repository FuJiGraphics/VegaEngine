#include "stdafx.h"
#include "Scene.h"
#include <algorithm>

Scene::Scene(SceneIDs id)
    : id(id)
    , objects()
{
    // Empty
}

void Scene::Init()
{
    for (auto obj : objects)
    {
        obj->Init();
    }
}

void Scene::Release()
{
    for (auto obj : objects)
    {
        obj->Release();
        delete obj;
    }
}

void Scene::Enter()
{
    for (auto obj : objects)
    {
        obj->Reset();
    }
}

void Scene::Exit()
{
}

void Scene::Update(float dt)
{
    for (auto obj : objects)
    {
        if (!obj->IsActive())
            continue;

        obj->Release();
    }
}

void Scene::Draw(sf::RenderWindow& window)
{
    for (auto obj : objects)
    {
        if (!obj->IsActive())
            continue;

        obj->Draw(window);
    }
}

void Scene::RemoveGo(GameObject* obj)
{
    objects.remove(obj);
}

GameObject* Scene::FindGo(const std::string& name)
{
    GameObject* result = nullptr;
    auto iter = std::find_if(objects.begin(), objects.end(),
        [name](GameObject* element)
        {
            return (name == element->GetName());
        });
    if (iter != objects.end())
    {
        result = (*iter);
    }
    return (result);
}

int Scene::FindGoAll(const std::string& name, std::list<GameObject*>& list)
{
    int count = 0;
    auto iter = std::find_if(objects.begin(), objects.end(),
        [name, &count, &list](GameObject* element)
        {
            if (element->GetName() == name)
            {
                count++;
                list.push_back(element);
            }
            return (false);
        });
    return (count);
}
