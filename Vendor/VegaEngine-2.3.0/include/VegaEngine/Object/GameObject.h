#pragma once
#include "Core/Core.h"
#include "Core/Layer.h"

namespace fz {

	class GameObject : public Layer
	{
	public:
		void OnAttach() override {};
		void OnDetach() override {};
		void OnEvent(fz::Event& event) override {};
		void OnUpdate(float dt) override {};
		void OnDraw(sf::RenderTexture& device) override {};
		void OnUI(sf::RenderTexture& device) override {};
		void OnImGui() override {};
		void OnCollide(Layer* pLayer, const std::string& className) override {};

	private:

	};


}  // namespace fz