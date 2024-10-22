#include "Scene.h"

namespace fz {
	Scene::Scene()
		: m_LayerList()
		, m_SceneID("")
	{
		// Empty
	}

	Scene::~Scene()
	{
		this->Release();
	}

	void Scene::Init(const std::string& sceneID)
	{
		m_SceneID = sceneID;
	}
	
	void Scene::Release()
	{
		m_LayerList.clear();
		m_SceneID = "";
	}

	void Scene::Event(EventList& events)
	{
		for (auto event : events)
		{
			if (event.empty())
				continue;
			for (auto layer : m_LayerList)
			{
				// 이벤트는 활성화 여부와 상관없이 동작하도록 함
				layer->OnEvent(event);
			}
		}
	}

	void Scene::Update(float dt)
	{
		for (auto layer : m_LayerList)
		{
			if (layer->IsActivated())
				layer->OnUpdate(dt);
		}
	}

	void Scene::Draw(fz::Window& window)
	{
		for (auto layer : m_LayerList)
		{
			if (layer->IsActivated())
				layer->OnDraw(window.GetFrameBuffer());
		}
	}

	void Scene::DrawGui()
	{
		for (auto layer : m_LayerList)
		{
			if (layer->IsActivated())
				layer->OnGui();
		}
	}

	void Scene::Collision()
	{
		for (auto layer : m_LayerList)
		{
			if (layer->IsActivated())
			{
				layer->OnGui();
			}
		}
	}

} // namespace fz