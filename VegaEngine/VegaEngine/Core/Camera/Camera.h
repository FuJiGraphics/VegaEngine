#pragma once
#include "Core/Core.h"
#include "Core/Layer/Layer.h"
#include "Core/Layer/Layer.h"

namespace fz {

	class Camera : public sf::RenderTexture
	{
	//// Delete, Enum, Using
	protected:
		// Delete
		Camera(const Camera&) = delete;
		Camera& operator=(const Camera&) = delete;

	//// Member Functions
	public:
		// Constructor, Destructor
		Camera();
		virtual ~Camera();

		// Impl
		void draw(const sf::Drawable& obj, const sf::RenderStates& states = sf::RenderStates::Default);
		void draw(Layer* object, const sf::RenderStates& states = sf::RenderStates::Default);
		void SetCenter(const sf::Vector2f& pos);
		void SetRotate(float rotate);
		void SetZoom(float factor);
		void Move(const sf::Vector2f& preset);
		// 카메라 뷰포트의 이동 가능 범위를 설정한다.
		void SetBlockArea(float x, float y, float width, float height);

		// Inlines
		inline void SetName(const std::string& name)	{ m_Name = name; }
		inline std::string GetName() const				{ return m_Name; }
		// TODO: 임시
		void SetTarget(Layer* layer)					{ m_Target = layer; }

	//// Member Variables
	private:
		sf::FloatRect m_BlockArea;
		sf::View m_View;
		std::string m_Name;
		// TODO: 임시
		Layer* m_Target;
	};

} // namespace fz