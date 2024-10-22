#pragma once

#include "Core.h"
#include "Event.h"

namespace fz {

	class Collider;

	class Layer
	{
	public:
		explicit Layer();
		virtual ~Layer();

		// 인터페이스
		virtual void			OnAttach();
		virtual void			OnDetach();
		virtual void			OnEvent(fz::Event& event);
		virtual void			OnUpdate(float dt);
		virtual void			OnDraw(sf::RenderTexture& device);
		virtual void			OnUI(sf::RenderTexture& device);
		virtual void			OnImGui();
		virtual void			OnCollide(Layer* pLayer, const std::string& className);
		virtual std::string		GetName() const = 0;

		// 충돌 시스템
		bool					IsActivatedCollider() const;
		void					ActivateCollider(bool flags, const std::string& className);
		void					SetCollider(const sf::Vector2f& origin, const sf::FloatRect& rect, const sf::Vector2f& scale = {1.0f, 1.0f});
		void					SetColliderDisplayMode(bool enabled);

		// 기타
		static unsigned int		GetCount();

	private:
		static unsigned int		s_numOfLayers;
		Collider*				m_body;
	};

} // namespace fz