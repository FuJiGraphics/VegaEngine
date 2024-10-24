#include "Core/stdafx.h"
#include "Scene.h"

namespace fz {
	Scene::Scene()
		: m_LayerList()
		, m_ColliderList()
		, m_SceneID("")
	{
		// Empty
	}

	Scene::~Scene()
	{
		// Empty
	}

	void Scene::Init(const std::string& sceneID)
	{
		m_SceneID = sceneID;
	}
	
	void Scene::Release()
	{
		if (m_LayerList.empty())
			return;

		for (auto& layer : m_LayerList)
			layer->OnDetach();
		m_LayerList.clear();
		m_SceneID = "";
	}

	void Scene::Event(EventList& events)
	{
		for (auto event : events)
		{
			if (event->empty())
				continue;
			for (auto layer : m_LayerList)
			{
				// 이벤트는 활성화 여부와 상관없이 동작하도록 함
				layer->OnEvent(*event);
			}
		}
	}

	void Scene::Update(float dt)
	{
		for (auto layer : m_LayerList)
		{
			if (layer->IsActivated())
			{
				layer->OnUpdate(dt);
			}
		}
	}

	void Scene::UpdateCollider()
	{
		for (HitData& d : m_ColliderList)
		{
			// TODO: 최적화
			// colRect 불필요
			auto c = d.GetCollider();
			auto p = d.GetLayer();
			auto& colBox = c->GetBox();
			auto& colRect = c->GetRect();
			auto& colOrigin = colBox.getOrigin();
			auto newPos = p->GetPosition();
			auto playerSize = p->GetSize();
			auto colPos = p->GetCollidePos();
			auto colSize = p->GetCollideSize();
			float newSizeX = (colSize.x) ? (float)colSize.x : (float)playerSize.x;
			float newSizeY = (colSize.y) ? (float)colSize.y : (float)playerSize.y;
			float newX = newPos.x + colOrigin.x + colPos.x;
			float newY = newPos.y + colOrigin.y + colPos.y;
			colBox.setPosition(newX, newY);
			colBox.setScale(p->GetScale());
			colBox.setOrigin(p->GetOrigin());
			colBox.setSize({ newSizeX, newSizeY });
			auto newRect = colBox.getGlobalBounds();
			colRect = { (int)newRect.left, (int)newRect.top, (int)newRect.width, (int)newRect.height };
		}
	}

	void Scene::Draw(fz::Window& window)
	{
		for (auto layer : m_LayerList)
		{
			if (layer->IsActivated())
				layer->OnDraw(window.GetCamera());
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

	void Scene::DrawCollisionSystem(fz::Window& window)
	{
		m_ColliderList.Display(window);
	}

	void Scene::Collision()
	{
		// TODO: 정렬 구조 개선 필요 현재 시간복잡도: n^2
		for (HitData& d1 : m_ColliderList)
		{
			for (HitData& d2 : m_ColliderList)
			{
				if (d1.ClassName() != d2.ClassName())
				{
					Layer* p1 = d1.GetLayer();
					Layer* p2 = d2.GetLayer();
					Collider* c1 = d1.GetCollider();
					Collider* c2 = d2.GetCollider();
					if (c1->IsCollided(*c2))
					{
						p1->OnCollide(d2);
						p2->OnCollide(d1);
					}
				}
			}
		}
	}

	void Scene::InsertCollideSystem(Layer* layer)
	{
		m_ColliderList.insert(layer);
	}

} // namespace fz