#pragma once
#include <VegaEngine2.h>
#include "MonsterFSM.h"

namespace fz {

	class Mushmom : public VegaScript, public MonsterFSM
	{
	public:
		float jumpCooldown = 0.45f; // ���� ��Ÿ�� 0.2��
		float jumpTimer = 0.0f;    // ���� Ÿ�̸�


		float JumpPower = -500.f;
		float MoveSpeed = 100.f;

		Animator animator;
		AnimationClip idle;
		AnimationClip move;
		AnimationClip damaged;
		AnimationClip die;
		AnimationClip skill1;


		TransformComponent* transform;
		RigidbodyComponent* body;

		void Start() override
		{
			transform = &GetComponent<TransformComponent>();
			body = &GetComponent<RigidbodyComponent>();
			sf::Sprite& sprite = GetComponent<SpriteComponent>();
			animator.SetTarget(sprite, *transform);
			animator.SetSpeed(1.0f);
			idle.loadFromFile("json/Animation/mushmom_idle.anim");
			move.loadFromFile("json/Animation/mushmom_move.anim");
			damaged.loadFromFile("json/Animation/mushmom_damaged.anim");
			die.loadFromFile("json/Animation/mushmom_die.anim");
			skill1.loadFromFile("json/Animation/mushmom_skill1.anim");

			body->SetGravityScale(1.5f);
		}

		void OnDestroy() override
		{
			FZLOG_DEBUG("�ӽ��� ��ũ��Ʈ �ı�! {0} {1}", 1.1, "aSDASCA");
		}

		void OnUpdate(float dt) override
		{
			if (!HasComponent<RigidbodyComponent>())
				return;

			animator.Update(dt);
			jumpTimer -= dt;
			// �̵� ����
			if (Input::IsKeyPressed(KeyType::D))
			{
			
				this->Move(Directions::RIGHT);
		//		if (Input::IsKeyDown(KeyType::D) && jumpTimer <= 0.0f && body->IsOnGround())
				//{
					this->Jump();
				//	jumpTimer = jumpCooldown; // Ÿ�̸� ����
			//	}
			}
			else if (Input::IsKeyPressed(KeyType::A))
			{

					this->Move(Directions::LEFT);
				//	if (Input::IsKeyDown(KeyType::D) && jumpTimer <= 0.0f && body->IsOnGround())
				//	{
						this->Jump();
					//	jumpTimer = jumpCooldown; // Ÿ�̸� ����
				//	}
			}
			else if (Input::IsKeyPressed(KeyType::Q))
			{
				this->Damaged();
			}
			else if (Input::IsKeyPressed(KeyType::W))
			{
				this->Die();
			}


			else
			{
				this->Idle();
			}

			//// ���� ó��
			//if (Input::IsKeyDown(KeyType::Space))
			//{
			//	this->Jump();
			//}


		}

		void Idle() override
		{
			animator.Play(&idle);
		}

		void Move(Directions dir) override
		{
			fz::Transform& transform = GetComponent<TransformComponent>();

			// �̵� ����
			if (dir == Directions::RIGHT)
			{
				body->AddPosition({ MoveSpeed * 1.f, 0.0f });
				transform.SetScale(-1.0f, 1.0f);

					animator.Play(&move);

			}
			else if (dir == Directions::LEFT)
			{
				body->AddPosition({ MoveSpeed * -1.f, 0.0f });

				transform.SetScale(1.0f, 1.0f);
		
					animator.Play(&move);
				
			}
		}

		void Jump() override
		{
			// �ٴڿ� ������ ���� ���� ����
			if (body->IsOnGround())
			{
				body->AddPosition({ 0.0f, JumpPower });
			}
		}

		void Damaged() override
		{
			// �÷��̾� �ǰݽ�
			animator.Play(&damaged);
		}

		void Die() override
		{
			animator.Play(&die);
		}

		void Skill1() override
		{
			animator.Play(&skill1);
		}

	private:

	};

}

BIND_SCRIPT(Mushmom, "8fc401b3-19ba-4183-833f-2cf6b0c13d01", "Mushmom", Mushmom);




