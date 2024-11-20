#include "pch.h"
#include "Scene.h"
#include "Entity.h"
#include "ScriptableEntity.h"

namespace fz {

	namespace {
		static b2BodyType ToBox2dBodyType(const fz::RigidbodyComponent::BodyType& rigidType)
		{
			switch (rigidType)
			{
				case RigidbodyComponent::BodyType::Static:
					return b2BodyType::b2_staticBody;
				case RigidbodyComponent::BodyType::Dynamic:
					return b2BodyType::b2_dynamicBody;
				case RigidbodyComponent::BodyType::Kinematic:
					return b2BodyType::b2_kinematicBody;
				default:
					FZLOG_ASSERT(false, "타입 변환을 할 수 없습니다. 알 수 없는 타입입니다.");
					break;
			}
			return b2BodyType();
		}
	}

	Scene::Scene(unsigned int width, unsigned int height, unsigned int mulltisampleLevel, const std::string& uuid)
		: m_UUID(uuid.empty() ? Random.GetUUID() : uuid)
		, m_World(nullptr)
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

	void Scene::StartPhysics()
	{
		StopPhysics();
		m_World = new b2World({ 0.0f, 9.8f });

		auto view = m_Registry.view<RigidbodyComponent>();
		for (auto& handle : view)
		{
			fz::Entity entity = { handle, shared_from_this() };
			auto& transformComp = entity.GetComponent<TransformComponent>();
			auto& rigidBodyComp = entity.GetComponent<RigidbodyComponent>();
			const auto& translate = transformComp.Transform.GetTranslate();
			const auto& rotation = transformComp.Transform.GetRotation();
			const auto& scale = transformComp.Transform.GetScale();

			b2BodyDef bodyDef;
			bodyDef.type = b2BodyType::b2_dynamicBody;
			bodyDef.position.Set(translate.x, translate.y);
			bodyDef.angle = Utils::DegreeToRadian(rotation);
			b2Body* body = m_World->CreateBody(&bodyDef);
			body->SetFixedRotation(rigidBodyComp.FixedRotation);
			rigidBodyComp.RuntimeBody = body;

			if (!entity.HasComponent<ColliderComponent>())
			{
				auto& collider = entity.AddComponent<ColliderComponent>();

				b2PolygonShape polygonShape;
				polygonShape.SetAsBox(collider.Size.x * scale.x, collider.Size.y * scale.y);

				b2FixtureDef fixtureDef;
				fixtureDef.shape = &polygonShape;
				fixtureDef.density = collider.Density;
				fixtureDef.friction = collider.Friction;
				fixtureDef.restitution = collider.Restitution;
				fixtureDef.restitutionThreshold = collider.RestitutionThreshold;
				body->CreateFixture(&fixtureDef);
			}
		}
	}

	void Scene::StopPhysics()
	{
		if (m_World)
		{
			delete m_World;
			m_World = nullptr;
		}
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

		// 물리 시스템 업데이트
		if (m_World)
		{
			const int32_t velocityIterations = 6;
			const int32_t positionIterations = 2;
			m_World->Step(dt, velocityIterations, positionIterations);

			auto view = m_Registry.view<RigidbodyComponent>();
			for (auto e : view)
			{
				Entity entity = { e, shared_from_this() };
				auto& transformComp = entity.GetComponent<TransformComponent>();
				auto& transform = transformComp.Transform;
				auto& rigid = entity.GetComponent<RigidbodyComponent>();
				b2Body* body = (b2Body*)rigid.RuntimeBody;
				const auto& bodyPos = body->GetPosition();
				const auto& bodyRot = Utils::RadianToDegree(body->GetAngle());
				transform.SetTranslate(bodyPos.x, bodyPos.y);
				transform.SetRotation(bodyRot);
			}
		}


		// 차일드 엔티티 트랜스폼 업데이트
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
					if (transform.IsChildRenderMode)
						cameraTransform = &transform.RenderTransform;
					else
						cameraTransform = &transform.Transform;
					mainCamera = &camera.Camera;
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