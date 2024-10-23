#pragma once

namespace fz {
	
	class Scene;
	class SceneList;

	class SceneManager
	{
	//// Member Functions
	public:
		// Impl
		static Scene* GetCurrentScene();
		static void InsertScene(const std::string& sceneID);
		static void RemoveScene(const std::string& sceneID);
		static void ChangeScene(const std::string& sceneID);

		static void Event(EventList& events);
		static void Update(float dt);
		static void Draw(fz::Window& window);
		static void DrawGui();
		static void Collision();

		// new, delete
		static void Release();
		
	private:
		static SceneList s_SceneList;
	};

} // namespace fz
