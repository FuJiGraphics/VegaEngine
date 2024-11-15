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
		if (ImGui::Begin("Hierarchy"))
		{
			if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered(0))
			{
				m_SelectionContext = {};
			}

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

		if (ImGui::Begin("Properties"))
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
			VegaUI::InputText(tag, "Tag");
		}

		if (entity.HasComponent<TransformComponent>())
		{
			auto& transform = entity.GetComponent<TransformComponent>().Transform;
			sf::Vector2f translate = transform.GetTranslate();
			float rotation = transform.GetRotation();
			sf::Vector2f scale = transform.GetScale();
			sf::Vector2f origin = transform.GetOrigin();

			if (ImGui::TreeNodeEx("TransformComponent1", ImGuiTreeNodeFlags_DefaultOpen, "Translate"))
			{
				if (VegaUI::DrawControl("Translate", translate))
					transform.SetTranslate(translate);
				ImGui::TreePop();
			}
			if (ImGui::TreeNodeEx("TransformComponent2", ImGuiTreeNodeFlags_DefaultOpen, "Scale"))
			{
				if (VegaUI::DrawControl("Scale", scale))
					transform.SetScale(scale);
				ImGui::TreePop();
			}
			if (ImGui::TreeNodeEx("TransformComponent3", ImGuiTreeNodeFlags_DefaultOpen, "Rotation"))
			{
				if (VegaUI::DragFloat(rotation, "Rotation"))
					transform.SetRotation(rotation);
				ImGui::TreePop();

			}
		}

		if (entity.HasComponent<CameraComponent>())
		{
			if (ImGui::TreeNodeEx("CameraComponent", ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
			{
				auto& cameraComp = entity.GetComponent<CameraComponent>();
				ImGui::Checkbox("Main", &cameraComp.Primary);
				ImGui::Checkbox("Fixed Aspect Ratio", &cameraComp.FixedAspectRatio);
				sf::FloatRect viewport = cameraComp.Camera.GetViewport();
				if (VegaUI::DragFloat4(viewport, "Viewport", true, 0.01))
				{
					if (viewport.width > viewport.left && viewport.height > viewport.top)
						cameraComp.Camera.SetViewport(viewport);
				}
				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<SpriteComponent>())
		{
			if (ImGui::TreeNodeEx("SpriteComponent", ImGuiTreeNodeFlags_DefaultOpen, "Sprite"))
			{
				SpriteComponent& spriteComp = entity.GetComponent<SpriteComponent>();
				sf::Sprite& sprite = spriteComp.Sprite;
				sf::Color color = sprite.getColor();
				if (VegaUI::ColorEdit4(color, "Color", true))
				{
					sprite.setColor(color);
				}
				ImGui::TreePop();
			}
		}
	}

} // namespace fz