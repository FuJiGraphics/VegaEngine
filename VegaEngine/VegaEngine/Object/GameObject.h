#pragma once
#include "Core/Core.h"
#include "Core/Layer/Layer.h"

namespace fz {

	class GameObject : public Layer
	{
	//// Delete, Enum, Using
	protected:
		// Delete
		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;

	public:
		// Contructor, Destructor                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
		GameObject();
		virtual ~GameObject();

		// overrides
		void OnAttach() override {};
		void OnDetach() override {};
		void OnEvent(fz::Event& event) override {};
		void OnUpdate(float dt) override {};
		void OnDraw(Camera& camera) override {};
		void OnGui() override {};
		void OnCollide(const HitData& hit) override {};
	};


}  // namespace fz