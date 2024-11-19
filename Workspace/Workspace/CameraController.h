#pragma once
#include "VegaEngine2.h"

namespace fz {

	class CameraController : public ScriptableEntity
	{
	public:
		void OnCreate()
		{
		}

		void OnDestroy()
		{
		}

		void OnUpdate(float dt)
		{
			auto& transformComponent = GetComponent<TransformComponent>();
			auto& transform = transformComponent.Transform;
			auto prevPos = transform.GetTranslate();
			if (InputManager::IsKeyPressed(KeyType::W))
			{
				prevPos.y -= m_Speed * dt;
				transform.SetTranslate(prevPos);
			}
			if (InputManager::IsKeyPressed(KeyType::S))
			{
				prevPos.y += m_Speed * dt;
				transform.SetTranslate(prevPos);
			}
			if (InputManager::IsKeyPressed(KeyType::A))
			{
				prevPos.x -= m_Speed * dt;
				transform.SetTranslate(prevPos);
			}
			if (InputManager::IsKeyPressed(KeyType::D))
			{
				prevPos.x += m_Speed * dt;
				transform.SetTranslate(prevPos);
			}
		};

	private:
		float m_Speed = 400.f;
	};
}

BIND_SCRIPT(1, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "EditorCamera", CameraController);
