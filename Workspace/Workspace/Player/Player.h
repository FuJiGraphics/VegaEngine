#pragma once
#include "VegaEngine2.h"
#include "PlayerStatus.h"

namespace fz {

	struct MutilpleKey
	{
		KeyType key1 = KeyType::Unknown;
		KeyType key2 = KeyType::Unknown;
	};

	class Player : public VegaScript
	{
	protected:
		using AnimType = PlayerStatus::Type;
		AnimType& CurrentType = PlayerStatus::Status;

	public:
		MutilpleKey InputKey;

		float Speed = 110.f;
		float JumpPower = -300.f;
		float IdleElap = 0.0f;
		float IdleTime = 1.0f;
		float AttackElap = 0.3f;
		float AttackTime = 0.3f;

		void Start() override
		{
		}

		void OnDestroy() override
		{

		}

		void OnUpdate(float dt) override
		{
			IdleElap += dt;
			AttackElap += dt;

			auto& body = GetComponent<RigidbodyComponent>();
			auto& transform = GetComponent<TransformComponent>();
			float fx = Input::GetAxis(Axis::Horizontal);
			float fy = Input::GetAxis(Axis::Vertical);

			body.SetGravityScale(0.85f);
			sf::Vector2f velocity = body.GetLinearVelocity();
			sf::Vector2f movement;

			const auto& scale = transform.Transform.GetScale();
			if (InputManager::IsKeyPressed(KeyType::D))
			{
				InputKey.key1 = KeyType::D;
				movement = { Speed * fx, velocity.y };
				if (body.IsOnGround())
				{
					float scaleX = (scale.x * -1.0f > 0.0f) ? scale.x * -1.0f : scale.x;
					transform.Transform.SetScale(scaleX, scale.y);
					if (InputManager::IsKeyPressed(KeyType::Space))
					{
						InputKey.key2 = KeyType::Space;
						movement = { velocity.x, JumpPower };
					}
				}
			}
			else if (InputManager::IsKeyPressed(KeyType::A))
			{
				InputKey.key1 = KeyType::A;
				movement = { Speed * fx, velocity.y };
				if (body.IsOnGround())
				{
					float scaleX = (scale.x * -1.0f < 0.0f) ? scale.x * -1.0f : scale.x;
					transform.Transform.SetScale(scaleX, scale.y);
					if (InputManager::IsKeyPressed(KeyType::Space))
					{
						InputKey.key2 = KeyType::Space;
						movement = { velocity.x, JumpPower };
					}
				}
			}
			else
			{
				movement = { 0, velocity.y };
				if (body.IsOnGround())
				{
					if (InputManager::IsKeyPressed(KeyType::Space))
					{
						InputKey.key1 = KeyType::Space;
						movement = { velocity.x, JumpPower };
					}
				}
			}

			if (AttackElap >= AttackTime && InputManager::IsKeyPressed(KeyType::Z))
			{
				AttackElap = 0.0f;
				InputKey.key1 = KeyType::Z;
				GameObject obj = FZ_CURRENT_SCENE->GetEntityFromTag("Bullet");
				float angle = Utils::Angle({ fx, fy });
				sf::Vector2f pos = transform.Transform.GetTranslate();
				pos.y += -15.f;
				sf::Vector2f dir = Utils::GetRotateVector(angle, sf::Vector2f(20.f, 0.0f));
				FZ_CURRENT_SCENE->Instantiate(obj, pos + dir, angle);
			}

			UpdateAnimStatus();
			body.SetLinearVelocity(movement);
		};

		void UpdateAnimStatus()
		{
			auto& body = GetComponent<RigidbodyComponent>();

			if (InputKey.key1 == KeyType::Z)
			{
				CurrentType = AnimType::IdleAttack;
			}
			if (InputKey.key1 == KeyType::A || InputKey.key1 == KeyType::D)
			{
				if (AttackElap >= AttackTime) {
					if (InputKey.key2 == KeyType::Space)
						CurrentType = AnimType::RunJump;
					else if (body.IsOnGround())
						CurrentType = AnimType::Run;
				}
			}

			if (InputKey.key1 == KeyType::Space)
			{
				if (AttackElap >= AttackTime) {
					CurrentType = AnimType::IdleJump;
				}
			}
			if (body.IsOnGround() && InputKey.key1 == KeyType::Unknown)
			{
				if (AttackElap >= AttackTime) {
					CurrentType = AnimType::Idle;
				}
			}
			InputKey.key1 = KeyType::Unknown;
			InputKey.key2 = KeyType::Unknown;
		}
	};
	
} // namespace fz

// 엔진이 사용할 팩토리 함수
//extern "C" __declspec(dllexport) fz::VegaScript* CreateScript() {
//	return new fz::Player();
//}

BIND_SCRIPT(Player, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "Player", Player);
