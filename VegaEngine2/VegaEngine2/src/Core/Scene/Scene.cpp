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

	Shared<Framebuffer>& Scene::GetFrameBuffer()
	{
		return m_FrameBuffer;
	}

	const Shared<Framebuffer>& Scene::GetFrameBuffer() const
	{
		return m_FrameBuffer;
	}

} // namespace fz