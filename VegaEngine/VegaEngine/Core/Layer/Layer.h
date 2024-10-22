#pragma once

#include "Core/Core.h"
#include "Core/Event/Event.h"
#include "Core/Collider/Collider.h"
#include "Core/Collider/HitData.h"

namespace fz {

	class Layer
	{
	//// Delete, Enum, Using
	protected:
		// Delete
		Layer(const Layer&) = delete;
		void operator=(const Layer&) = delete;

	//// Member Functions
	public:
		// Constructor, Destructor
		Layer();
		virtual ~Layer();

		// Virtuals 
		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnEvent(fz::Event& event);
		virtual void OnUpdate(float dt);
		virtual void OnDraw(sf::RenderTexture& device);
		virtual void OnGui();
		virtual void OnCollide(const HitData& hit);

		// ** Set ClassName **
		virtual std::string GetClassName() const = 0;
	};

} // namespace fz