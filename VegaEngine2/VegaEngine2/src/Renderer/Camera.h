#pragma once

#include "Core/Core.h"

namespace fz {

	class OrthoCamera
	{
	protected:
		// Using
		using Super = fz::OrthoCamera;
		// Delete
		FZ_DELETE_COPY(OrthoCamera)

	public:
        OrthoCamera(const std::string& name);
        OrthoCamera(const std::string& name, const sf::FloatRect& rectangle);
        OrthoCamera(const std::string& name, const sf::Vector2f& center, const sf::Vector2f& size);
		virtual ~OrthoCamera() = default;

        void SetCenter(float x, float y);
        void SetCenter(const sf::Vector2f& center);
        void SetSize(float width, float height);
        void SetSize(const sf::Vector2f& size);
        void SetRotation(float angle);
        void SetViewport(const sf::FloatRect& viewport);
        void Reset(const sf::FloatRect& rectangle);
        const sf::Vector2f& GetCenter() const;
        const sf::Vector2f& GetSize() const;
        float GetRotation() const;
        const sf::FloatRect& GetViewport() const;
        void Move(float offsetX, float offsetY);
        void Move(const sf::Vector2f& offset);
        void Rotate(float angle);
        void Zoom(float factor);
        const sf::Transform& GetTransform() const;
        const sf::Transform& GetInverseTransform() const;

	private:
        std::string m_Name;
		sf::View	m_View;
	};


} // namespace fz