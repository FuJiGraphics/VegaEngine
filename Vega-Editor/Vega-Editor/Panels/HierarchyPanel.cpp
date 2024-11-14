#include "HierarchyPanel.h"

namespace fz {

	HierarchyPanel::HierarchyPanel(const Shared<Scene>& scene)
		: m_Context(nullptr)
	{
		SetContext(scene);
	}

	void HierarchyPanel::SetContext(const Shared<Scene>& scene)
	{
		m_Context = scene;
	}

	void HierarchyPanel::OnImGuiRender()
	{
		ImGui::Begin("Scene Hierarchy");

		if (m_Context)
		{
			auto view = m_Context->m_Registry.view<TagComponent>();
			view.each([this](entt::entity entityID, const TagComponent& tagComp)
					  {
						  Entity entity = { entityID, m_Context };
						  this->DrawTreeNode(entity, tagComp.Tag.c_str());
					  });

		}

		ImGui::End();
	}

	void HierarchyPanel::DrawTreeNode(const fz::Entity& entity, const char* tag)
	{
		ImGuiTreeNodeFlags flag = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((const void*)(std::uint64_t)(std::uint32_t)entity, flag, tag);
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		if (opened)
		{
			ImGui::TreePop();
		}
	}

} // namespace fz