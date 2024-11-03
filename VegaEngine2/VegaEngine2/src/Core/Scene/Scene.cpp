#include "pch.h"
#include "Scene.h"

namespace fz {
	Scene::Scene()
	{

		struct TransformComponent
		{
			sf::Vector2f	Position;
			float			Rotation;
			sf::Vector2f	Scale;

			TransformComponent() = default;
			TransformComponent(const TransformComponent&) = default;
			TransformComponent(const sf::Vector2f& pos, float rot, const sf::Vector2f& scale)
				: Position(pos)
				, Rotation(rot)
				, Scale(scale)
			{
				// Empty
			}
		};

		entt::entity entity = m_Registry.create();

		m_Registry.emplace<TransformComponent>(entity, sf::Vector2f{0.0, 0.0f}, 0.0f, sf::Vector2f{1.0f, 1.0f});


	}

	Scene::~Scene()
	{
	}

} // namespace fz