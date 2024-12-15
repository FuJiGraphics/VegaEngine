#pragma once
#include <VegaEngine2.h>

namespace fz {

	class UIScript : public VegaScript
	{
	public:
		TransformComponent* transform;
		GameObject target;
		sf::Vector2f size;

		void Start() override
		{
			transform = &GetComponent<TransformComponent>();
			target = GetCurrentScene()->GetEntityFromTag("Camera");
			const sf::Vector2f& pos = target.GetComponent<TransformComponent>().Transform.GetTranslate();
			transform->Transform.SetTranslate(pos);
			const auto& viewport = GetCurrentScene()->GetViewportSize();
			const auto& ui = GetCurrentScene()->GetEntityFromTag("BottomBackground").GetComponent<SpriteComponent>();
			size = { (float)ui.Sprite.GetSize().x, (float)ui.Sprite.GetSize().y };
		}

		void OnDestroy() override
		{

		}

		void OnUpdate(float dt) override
		{
			const auto& viewport = GetCurrentScene()->GetViewportSize();
			const sf::Vector2f& pos = target.GetComponent<TransformComponent>().Transform.GetTranslate();
			float zoom = target.GetComponent<CameraComponent>().Camera.GetZoom();
			float dw = (viewport.x / size.x) * zoom;
			float dh = ((viewport.y * 0.125f) / size.y) * zoom;
			float posY = pos.y + (viewport.y * 0.5f) - size.y * 2.1f;
 			transform->Transform.SetTranslate({ pos.x, posY });
			transform->Transform.SetScale(dw, dh);
		}

		void OnTriggerEnter(Collider collider) override
		{

		}

		void OnTriggerStay(Collider collider) override
		{

		}

		void OnTriggerExit(Collider collider) override
		{

		}
	};
} // namespace fz

