#pragma once
#include <VegaEngine2.h>

namespace fz {

	class Editor2D : public fz::Layer
	{
	public:
		Editor2D(const std::string& name);

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(float dt) override;
		void OnEvent(fz::Event& ev) override;
		void OnUI() override;

	private:
		CameraController m_CameraController;
		Shared<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		unsigned int texId;
	};

} // namespace fz