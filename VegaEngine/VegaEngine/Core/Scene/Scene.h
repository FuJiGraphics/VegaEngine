#pragma once
#include "Core/Layer/LayerList.h"
#include "Core/Event/EventList.h"
#include "Core/Collider/ColliderList.h"
#include "Core/Window.h"

namespace fz {

	class Scene final
	{
	//// Delete, Enum, Using
	protected:
		// Using
		using Super = Scene;

		// Delete
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;

	//// Member Functions
	public:
		// Constructor, Destructor
		Scene();
		virtual ~Scene();

		// Impl
		void Init(const std::string& sceneID);
		void Release();

		void Event(EventList& events);
		void Update(float dt);
		void UpdateCollider();
		void Draw(fz::Window& window);
		void DrawGui();
		void DrawCollisionSystem(fz::Window& window);
		void Collision();
		void InsertCollideSystem(Layer* layer);

		template<typename T>
		T* InsertObject(T* obj);
		template<typename T>
		T* InsertOverlay(T* overlay);
		template<typename T>
		void RemoveObject(T* obj);
		template<typename T>
		void RemoveOverlay(T* overlay);

		// Inlines
		inline std::string GetSceneID() const { return m_SceneID; }
		inline ColliderList& GetColliderList() { return m_ColliderList; }

	//// Member Variables
	private:
		LayerList m_LayerList;
		ColliderList m_ColliderList;
		std::string m_SceneID;
	};

	template<typename T>
	inline T* Scene::InsertObject(T* obj)
	{
		m_LayerList.AttachLayer(obj);
		return obj;
	}

	template<typename T>
	inline T* Scene::InsertOverlay(T* overlay)
	{
		m_LayerList.AttachOverlay(overlay);
		return overlay;
	}

	template<typename T>
	inline void Scene::RemoveObject(T* obj)
	{
		m_LayerList.remove(obj, Section::Right);
	}

	template<typename T>
	inline void Scene::RemoveOverlay(T* overlay)
	{
		m_LayerList.remove(overlay, Section::Left);
	}

} // namespace fz