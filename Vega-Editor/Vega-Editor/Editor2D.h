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
		Shared<Scene> CreateScene(unsigned int width, unsigned int height);
		void SaveScene(const Shared<Scene>& scene, const std::string& path);
		Shared<Scene> LoadScene(const std::string& path);

	private:
		std::string	m_ActiveSceneFilePath;
		Shared<Scene> m_ActiveScene;
		HierarchyPanel m_HierarchyPanel;
	};

} // namespace fz