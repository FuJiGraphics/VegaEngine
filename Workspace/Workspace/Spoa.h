#pragma once
#include <VegaEngine2.h>

namespace fz {

	class Spoa : public VegaScript
	{
	public:
		bool isJumping = false; // ���� ���� ����
		Animator animator;
		AnimationClip idle;
		AnimationClip move;
		AnimationClip hit;
		AnimationClip die;



		void Start() override
		{
			auto& transform = GetComponent<TransformComponent>();
			auto& body = GetComponent<RigidbodyComponent>();
			sf::Sprite& sprite = GetComponent<SpriteComponent>();
			body.SetGravityScale(1.5f);
			animator.SetTarget(sprite, transform);
			animator.SetSpeed(1.0f);
		

			bool flag5 = idle.loadFromFile("json/animation/spoa_anim.json");
			//bool flag2 = move.loadFromFile("json/animation/ribbon_pig_animMove.json");
			//bool flag3 = idle.loadFromFile("json/ribbon_pig_animHit.json");
			//bool flag4 = idle.loadFromFile("json/ribbon_pig_animDie.json");

		}

		void OnDestroy() override
		{
			FZLOG_DEBUG("������ ��ũ��Ʈ �ı�!{0} { 1 }", 1.1, "aSDASCA");
		}

		void OnUpdate(float dt) override
		{
			if (!HasComponent<RigidbodyComponent>())
				return;
			animator.Update(dt);

			/*	animator.Play(&idle);*/
		/*		animator.Play(&move);*/
			animator.Play(&idle);


			auto& body = GetComponent<RigidbodyComponent>();

			if (Input::IsKeyPressed(KeyType::D))
			{
				body.AddPosition({ 100.0, 0.0f });
			//	animator.Play(&move);
			}
			else if (Input::IsKeyPressed(KeyType::A))
			{
				body.AddPosition({ -100.0, 0.0f });
			//	animator.Play(&move);

			}

			// ���� ó��
			if (body.IsOnGround() && !isJumping)
			{
				if (Input::IsKeyPressed(KeyType::Space))
				{
					body.AddPosition({ 0.0f, -500.f });
					isJumping = true; // ���� ����
				}
			}

			// �ٴڿ� ������ ���� ���� ����
			if (body.IsOnGround())
			{
				isJumping = false;
			}

		}

	private:

	};

}

BIND_SCRIPT(Spoa, "ecc56651-ae87-4e4a-b05f-e8c5b14963c4", "Spoa", Spoa);
