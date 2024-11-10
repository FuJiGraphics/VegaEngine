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
		CameraController camera;
		Shared<Framebuffer>	frameBuffer;
		Shared<Scene> activeScene;
		Entity square;
		unsigned int texId;
	};

} // namespace fz