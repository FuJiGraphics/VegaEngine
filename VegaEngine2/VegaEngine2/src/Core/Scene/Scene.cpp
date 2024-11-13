#include "pch.h"
#include "Scene.h"
#include "Entity.h"

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
		// Empty
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

	void Scene::OnUpdate(float dt)
	{
		// 스프라이트 렌더링
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