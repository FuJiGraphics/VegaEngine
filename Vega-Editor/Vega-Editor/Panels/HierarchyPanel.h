#pragma once
#include <VegaEngine2.h>

namespace fz {

	class HierarchyPanel
	{
	public:
		HierarchyPanel(const Shared<Scene>& scene);

		void SetContext(const Shared<Scene>& scene);

		void OnImGuiRender();

	protected:
		void DrawTreeNode(const fz::Entity& entity, const char* tag);
		void DrawSceneComponents(fz::Entity& entity);

	private:
		Shared<Scene> m_Context;
		Entity m_SelectionContext;
		bool m_OnEntityRemove;
	};
}