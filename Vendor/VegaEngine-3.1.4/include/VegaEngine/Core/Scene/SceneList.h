#pragma once
#include "Core/Array.h"
#include "Scene.h"

namespace fz {

	class SceneList final : public Array<Scene*>
	{
	//// Delete, Enum, Using
	protected:
		// Delete
		SceneList(const SceneList&) = delete;
		void operator=(const SceneList&) = delete;

	//// Member Functions
	public:
		// Constructor, Destructor
		SceneList();
		virtual ~SceneList();

		// Impl
		void Release();

		void InsertScene(const std::string& sceneID);
		void RemoveScene(const std::string& sceneID);
		void ChangeScene(const std::string& sceneID);

		void Event(EventList& events);
		void Update(float dt);
		void Draw(fz::Window& window);
		void DrawGui();
		void Collision();

		// Inlines
		inline Iter GetCurrentScene()	{ return Super::begin() + m_CurrScene; }
		inline Iter GetNextScene()		{ return Super::begin() + m_CurrScene + 1; }

	private:
		int m_CurrScene;
	};

} // namespace fz