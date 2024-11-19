#include "pch.h"
#include "Scene.h"
#include "Entity.h"
#include "ScriptableEntity.h"

namespace fz {
	Scene::Scene(unsigned int width, unsigned int height, unsigned int mulltisampleLevel, const std::string& uuid)
		: m_UUID(uuid.empty() ? Random.GetUUID() : uuid)
	{
		FramebufferSpec frameSpec;
		frameSpec.Width = width;
		frameSpec.Height = height;
		frameSpec.MultisampleLevel = 1;
		m_FrameBuffer = Framebuffer::Create(frameSpec);
	}

	Scene::~Scene()
	{
		auto nativeView = m_Registry.view<NativeScriptComponent>();
		nativeView.each([&](auto entity, NativeScriptComponent& nsc)
						{
							if (nsc.Instance)
								nsc.OnDestroyFunction(nsc.Instance);
						});
	}

	Entity Scene::CreateEntity(const std::string& tagName)
	{
		Entity entity = { m_Registry.create(), shared_from_this() };
		auto& tagComp = entity.AddComponent<TagComponent>(tagName);
		if (tagComp.Tag.empty())
			tagComp.Tag = "Entity";
		if (!tagName.empty())
		{
			tagComp.Tag = tagName;
		}
		entity.AddComponent<TransformComponent>();
		m_EntityPool.insert({ entity.m_UUID, entity.m_Handle });
		return entity;
	}

	Entity Scene::CreateEntityWithUUID(const std::string& tagName, const std::string& uuid)
	{
		Entity entity = { m_Registry.create(), shared_from_this() };
		entity.m_UUID = uuid;
		auto& tagComp = entity.AddComponent<TagComponent>(tagName);
		if (tagComp.Tag.empty())
			tagComp.Tag = "Entity";
		if (!tagName.empty())
		{
			tagComp.Tag = tagName;
		}
		entity.AddComponent<TransformComponent>();
		m_EntityPool.insert({ entity.m_UUID, entity.m_Handle });
		return entity;
	}

	Entity Scene::CreateEntity(const std::string& uuid, const std::string& tagName)
	{
		Entity entity = { uuid, m_Registry.create(), shared_from_this() };
		auto& tagComp = entity.AddComponent<TagComponent>(tagName);
		if (tagComp.Tag.empty())
			tagComp.Tag = "Entity";
		if (!tagName.empty())
		{
			tagComp.Tag = tagName;
		}
		entity.AddComponent<TransformComponent>();
		m_EntityPool.insert({ entity.m_UUID, entity.m_Handle });
		return entity;
	}

	void Scene::DeleteEntity(fz::Entity& entity)
	{
		auto it = m_EntityPool.find(entity.m_UUID);
		if (it != m_EntityPool.end())
		{
			m_EntityPool.erase(it);
		}
		m_Registry.destroy(entity.m_Handle);
		entity.m_Handle = entt::null;
	}

	void Scene::OnUpdate(float dt)
	{
		// ��ũ��Ʈ ������Ʈ
		auto nativeView = m_Registry.view<NativeScriptComponent>();
		nativeView.each([&](auto entity, NativeScriptComponent& nsc)
						{
							if (nsc.Instance == nullptr)
							{
								nsc.Instance = nsc.CreateInstanceFunc();
								if(!nsc.Instance->m_Entity) 
									nsc.Instance->m_Entity = {entity, shared_from_this()};
								nsc.OnCreateFunction(nsc.Instance);
							}
							nsc.OnUpdateFunction(nsc.Instance, dt);
						});

		// ���ϵ� ��ƼƼ Ʈ������ ������Ʈ
		auto chileView = m_Registry.view<ChildEntityComponent>();
		for (auto childEntity : chileView)
		{
			auto& childComp = chileView.get<ChildEntityComponent>(childEntity);
			auto& parentTransform = childComp.ParentEntity.GetComponent<TransformComponent>();
			for (auto& childs : childComp.CurrentChildEntities)
			{
				TransformComponent& childTransform = childs.GetComponent<TransformComponent>();
				childTransform.IsChildRenderMode = true;
				childTransform.RenderTransform = parentTransform.Transform;
				childTransform.RenderTransform *= childTransform.Transform;
			}
		}

		// ī�޶� ������Ʈ
		OrthoCamera* mainCamera = nullptr;
		fz::Transform* cameraTransform = nullptr;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				const auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					if (transform.IsChildRenderMode)
						cameraTransform = &transform.RenderTransform;
					else
						cameraTransform = &transform.Transform;
					mainCamera = &camera.Camera;
					break;
				}
			}
		}

		// ��������Ʈ ������
		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, *cameraTransform, m_FrameBuffer);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteComponent>);
			for (auto entity : group)
			{
				const auto& [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);
				if (transform.IsChildRenderMode)
					Renderer2D::Draw(sprite.SortingOrder, sprite, transform.RenderTransform);
				else
					Renderer2D::Draw(sprite.SortingOrder, sprite, transform);

			}

			Renderer2D::EndScene();
		}
		else
		{
			m_FrameBuffer->Clear();
		}
	}

	void Scene::OnViewportResize(unsigned int width, unsigned int height)
	{
		if (width < 0 || height < 0)
			return;

		m_FrameBuffer->Resize(width, height);

		auto view = m_Registry.view<CameraComponent>();
		for (auto& entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
			{
 				cameraComponent.Camera.SetSize(width, height);
			}
		}
	}

	fz::Entity Scene::GetEntityFromUUID(const std::string& uuid)
	{
		auto it = m_EntityPool.find(uuid);
		std::string itUUID = "";
		entt::entity itHandle = entt::null;
		if (it != m_EntityPool.end())
		{
			itUUID = it->first;
			itHandle = it->second;
			
		}
		return fz::Entity(itUUID, itHandle, shared_from_this());
	}

	Entity Scene::GetEntityFromTag(const std::string& tag)
	{
		auto view = m_Registry.view<TagComponent>();
		for (auto& it : m_EntityPool)
		{
			Entity entity = { it.first, it.second, shared_from_this() };
			std::string targetTag = entity.GetComponent<TagComponent>().Tag;
			if (targetTag == tag)
				return entity;
		}
		return {};
	}

} // namespace fz