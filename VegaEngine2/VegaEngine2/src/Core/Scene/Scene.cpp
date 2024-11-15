#include "pch.h"
#include "Scene.h"
#include "Entity.h"
#include "ScriptableEntity.h"

namespace fz {
	Scene::Scene(unsigned int width, unsigned int height, unsigned int mulltisampleLevel)
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

		entity.AddComponent<TransformComponent>();
		return entity;
	}

	void Scene::DeleteEntity(fz::Entity& entity)
	{
		m_Registry.destroy(entity.m_Handle);
		entity.m_Handle = entt::null;
	}

	void Scene::OnUpdate(float dt)
	{
		// 스크립트 업데이트
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

		// 카메라 업데이트
		OrthoCamera* mainCamera = nullptr;
		fz::Transform* cameraTransform = nullptr;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				const auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera;
					cameraTransform = &transform;
					break;
				}
			}
		}

		// 스프라이트 렌더링
		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, *cameraTransform, m_FrameBuffer);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteComponent>);
			for (auto entity : group)
			{
				const auto& [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);
				Renderer2D::Draw(sprite, transform);
			}

			Renderer2D::EndScene();
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

} // namespace fz