#pragma once
#include "Core/Core.h"

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
		void draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
		void SetCenter(const sf::Vector2f& pos);
		void SetRotate(float rotate);
		void SetZoom(float factor);
		void Move(const sf::Vector2f& preset);

		// Inlines
		inline void SetName(const std::string& name) { m_Name = name; }
		inline std::string GetName() const { return m_Name; }

	//// Member Variables
	private:
		sf::View m_View;
		std::string m_Name;
	};

} // namespace fz