#include "HierarchyPanel.h"

using namespace std;

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
		if (ImGui::Begin("Scene Hierarchy"))
		{
			if (m_Context)
			{
				auto view = m_Context->m_Registry.view<TagComponent>();
				view.each([this](entt::entity entityID, const TagComponent& tagComp)
						  {
							  Entity entity = { entityID, m_Context };
							  this->DrawTreeNode(entity, tagComp.Tag.c_str());
						  });

			}
		}
		ImGui::End();

		if (ImGui::Begin("Draw Components"))
		{
			if (m_SelectionContext)
				this->DrawSceneComponents(m_SelectionContext);
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

	void HierarchyPanel::DrawSceneComponents(fz::Entity& entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;
			VegaUI::InputText("Tag", tag);
		}

		if (entity.HasComponent<TransformComponent>())
		{
			const auto& transform = entity.GetComponent<TransformComponent>().Transform;
			const auto& translate = transform.GetTranslate();
			const auto& rotation = transform.GetRotation();
			const auto& scale = transform.GetScale();
			const auto& origin = transform.GetOrigin();
			ImGui::Text("Translate: %s ", ((to_string(translate.x) + ", ") + to_string(translate.y)).c_str());

		}
	}

} // namespace fz