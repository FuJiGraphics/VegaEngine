#pragma once
#include <VegaEngine2.h>
#include "Panels/HierarchyPanel.h"

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

	protected:
		void SaveScene(const Shared<Scene>& scene);
		Shared<Scene> LoadScene(const std::string& path);

	private:
		Shared<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;
		HierarchyPanel m_HierarchyPanel;
		unsigned int texId;
	};

} // namespace fz