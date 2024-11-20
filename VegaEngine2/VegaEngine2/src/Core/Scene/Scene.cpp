#include "pch.h"
#include "Scene.h"
#include "Entity.h"
#include "ScriptableEntity.h"
#include "EditorCamera.h"

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
		, m_IsDebugMode(false)
	{
		FramebufferSpec frameSpec;
		frameSpec.Width = width;
		frameSpec.Height = height;
		frameSpec.MultisampleLevel = 8;
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
			auto& transform = transformComp.Transform;

			const b2Vec2& meterPos = Utils::PixelToMeter(transform.GetTranslate());

			b2BodyDef bodyDef;
			bodyDef.type = ToBox2dBodyType(rigidBodyComp.RigidType);
			bodyDef.position.Set(meterPos.x, meterPos.y);
			bodyDef.angle = Utils::DegreeToRadian(transform.GetRotation());
			b2Body* body = m_World->CreateBody(&bodyDef);
			body->SetFixedRotation(rigidBodyComp.FixedRotation);
			rigidBodyComp.RuntimeBody = body;

			if (entity.HasComponent<BoxCollider2DComponent>())
			{
				auto& collider = entity.GetComponent<BoxCollider2DComponent>();

				const b2Vec2& meterBoxSize = Utils::PixelToMeter({ collider.Size.x * transform.GetScale().x, 
																 collider.Size.y * transform.GetScale().y });

				b2PolygonShape polygonShape;
				polygonShape.SetAsBox(meterBoxSize.x, meterBoxSize.y);

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

	void Scene::OnUpdateEditor(float dt, EditorCamera& editorCamera)
	{
		this->OnUpdateChildEntity();
		editorCamera.OnUpdate(dt);
		this->OnRenderEditorSprite(&editorCamera.GetOrthoCamera());
	}

	void Scene::OnUpdateRuntime(float dt)
	{
		OrthoCamera* camera = nullptr;
		sf::Transform* transform = nullptr;
		this->OnUpdateScript(dt);
		this->OnUpdateChildEntity();
		this->OnUpdateCamera(&camera, &transform);
		this->OnUpdatePhysicsSystem(dt);
		this->OnRenderRuntimeSprite(camera, *transform);
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

	void Scene::OnUpdateScript(float dt)
	{
		auto nativeView = m_Registry.view<NativeScriptComponent>();
		nativeView.each([&](auto entity, NativeScriptComponent& nsc)
						{
							if (nsc.Instance == nullptr)
							{
								nsc.Instance = nsc.CreateInstanceFunc();
								if (!nsc.Instance->m_Entity)
									nsc.Instance->m_Entity = { entity, shared_from_this() };
								nsc.OnCreateFunction(nsc.Instance);
							}
							nsc.OnUpdateFunction(nsc.Instance, dt);
						});
	}

	void Scene::OnUpdateChildEntity()
	{
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
				childTransform.RenderTransform = parentTransform.Transform * childTransform.Transform;
			}
		}
	}

	void Scene::OnUpdatePhysicsSystem(float dt)
	{
		// 물리 시스템 업데이트
		if (m_World)
		{
			float timeStep = 1.0f / 60.0f; // 초당 60프레임
			const int32_t velocityIterations = 8;
			const int32_t positionIterations = 3;
			m_World->Step(timeStep, velocityIterations, positionIterations);

			auto view = m_Registry.view<RigidbodyComponent>();
			for (auto e : view)
			{
				Entity entity = { e, shared_from_this() };
				auto& transformComp = entity.GetComponent<TransformComponent>();
				auto& transform = transformComp.Transform;
				auto& rigid = entity.GetComponent<RigidbodyComponent>();
				b2Body* body = (b2Body*)rigid.RuntimeBody;
				if (body)
				{
					const sf::Vector2f& pixelBoxPos = Utils::MeterToPixel(body->GetPosition());
					const auto& bodyRot = Utils::RadianToDegree(body->GetAngle());
					transform.SetTranslate(pixelBoxPos.x, pixelBoxPos.y);
					transform.SetRotation(bodyRot);
				}
			}
		}
	}

	void Scene::OnUpdateCamera(OrthoCamera** dstCamera, sf::Transform** dstTransform)
	{
		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view)
		{
			const auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

			if (camera.Primary)
			{
				if (transform.IsChildRenderMode)
					*dstTransform = &transform.RenderTransform;
				else
					*dstTransform = &transform.Transform.GetRawTransform();
				*dstCamera = &camera.Camera;
				break;
			}
		}
	}

	void Scene::OnRenderEditorSprite(OrthoCamera* mainCamera)
	{
		// 스프라이트 렌더링
		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, m_FrameBuffer);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteComponent>);
			for (auto entity : group)
			{
				const auto& [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);
				if (transform.IsChildRenderMode)
					Renderer2D::Draw(sprite.SortingOrder, sprite, transform.RenderTransform);
				else
					Renderer2D::Draw(sprite.SortingOrder, sprite, transform.Transform);
			}

			// Debug Display Mode
			OnDrawDebugShape();
			Renderer2D::EndScene();
		}
		else
		{
			m_FrameBuffer->Clear();
		}
	}

	void Scene::OnRenderRuntimeSprite(OrthoCamera* mainCamera, sf::Transform& transform)
	{
		// 스프라이트 렌더링
		if (mainCamera)
		{
			Renderer2D::BeginScene(*mainCamera, transform, m_FrameBuffer);
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteComponent>);
			for (auto entity : group)
			{
				const auto& [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);
				if (transform.IsChildRenderMode)
					Renderer2D::Draw(sprite.SortingOrder, sprite, transform.RenderTransform);
				else
					Renderer2D::Draw(sprite.SortingOrder, sprite, transform.Transform);
			}
			// Debug Display Mode
			OnDrawDebugShape();
			Renderer2D::EndScene();
		}
		else
		{
			m_FrameBuffer->Clear();
		}
	}

	void Scene::OnDrawDebugShape()
	{
		if (!m_IsDebugMode)
			return;

		auto boxView = GetEntities<TransformComponent, BoxCollider2DComponent>();
		for (auto& handle : boxView)
		{
			const auto& [transformComp, boxComp] = boxView.get<TransformComponent, BoxCollider2DComponent>(handle);
			sf::RectangleShape* rect = new sf::RectangleShape;
			rect->setOutlineColor(sf::Color::Green);
			rect->setOutlineThickness(1.0f);
			rect->setFillColor(sf::Color::Transparent);
			rect->setSize({ boxComp.Size.x * 2.0f, boxComp.Size.y * 2.0f });
			rect->setPosition({ boxComp.Size.x * -1.0f, boxComp.Size.y * -1.0f });
			Renderer2D::Draw(rect, transformComp.Transform);
		}
		// auto circleView = GetEntities<TransformComponent, CircleCollider2DComponent>();
	}

} // namespace fz