#pragma once
#include "VegaEngine2.h"



namespace fz {

	class CameraController : public ScriptableEntity
	{
	public:
		void OnCreate()
		{
			auto& transform = GetComponent<TransformComponent>();
			transform.Transform.SetTranslate(0.0f, 0.0f);
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
		float m_Speed = 100.f;
	};
}

BIND_SCRIPT(1, "D:\\dev\\VegaEngine.ver2\\Resource\\json\\scene1.json", "Camera", CameraController);
