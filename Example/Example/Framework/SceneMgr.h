#pragma once

#include "Singleton.h"
#include "Defines.h"
#include "SFML/Graphics.hpp"
#include <vector>

class Scene;

class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;

protected:
	std::vector<Scene*>	scenes;

	SceneIDs startScene;
	SceneIDs currScene;

	SceneMgr() = default;
	virtual ~SceneMgr() = default;

	SceneMgr(const SceneMgr&) = delete;
	SceneMgr& operator=(const SceneMgr&) = delete;

public:
	void Init();
	void Release();

	void ChangeScene(SceneIDs id);
	void Updata(float dt);
	void Draw(sf::RenderWindow& window);

	SceneIDs GetCurrentScene() const { return (currScene); }
	int GetSize() const { return (scenes.size()); }
};
