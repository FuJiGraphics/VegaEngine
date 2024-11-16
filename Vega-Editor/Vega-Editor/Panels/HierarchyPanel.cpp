#include "HierarchyPanel.h"

using namespace std;

namespace fz {


	HierarchyPanel::HierarchyPanel(const Shared<Scene>& scene)
		: m_Context(nullptr)
		, m_OnEntityRemove(false)
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
			
			if (ImGui::BeginPopupContextWindow(0, 1))
			{
				if (ImGui::MenuItem("New Entity..."))
					m_Context->CreateEntity("NewEntity");

				ImGui::EndPopup();
			}

			if (m_Context)
			{
				auto view = m_Context->m_Registry.view<TagComponent>();
				view.each([this](entt::entity entityID, const TagComponent& tagComp)
						  {
							  Entity entity = { entityID, m_Context };
							  this->DrawTreeNode(entity, tagComp.Tag.c_str());
							  if (ImGui::BeginPopupContextItem(0, ImGuiPopupFlags_MouseButtonRight))
							  {
								  if (ImGui::MenuItem("Remove"))
								  {
									  m_OnEntityRemove = true;
									  m_SelectionContext = entity;
								  }
								  ImGui::EndPopup();
							  }
						  });
			}

			if (ImGui::Begin("Properties"))
			{
				if (m_SelectionContext)
					this->DrawSceneComponents(m_SelectionContext);
			}
			ImGui::End();

			if (m_OnEntityRemove)
			{
				m_OnEntityRemove = false;
				m_Context->DeleteEntity(m_SelectionContext);
				m_SelectionContext = {};
			}
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
		ImGuiTreeNodeFlags treeFlag = ImGuiTreeNodeFlags_DefaultOpen |
			ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Framed;
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;
			VegaUI::InputText(tag, "Tag");
		}

		{
			ImGui::SameLine();
			ImGui::PushItemWidth(-1);
			if (ImGui::Button("Add"))
			{
				ImGui::OpenPopup("AddComponent");
			}
			if (ImGui::BeginPopup("AddComponent"))
			{
				DisplayAddComponentEntry<CameraComponent>("Camera");
				DisplayAddComponentEntry<SpriteComponent>("Sprite");
				ImGui::EndPopup();
			} 
		}


		if (entity.HasComponent<TransformComponent>())
		{
			auto& transform = entity.GetComponent<TransformComponent>().Transform;
			sf::Vector2f translate = transform.GetTranslate();
			float rotation = transform.GetRotation();
			sf::Vector2f scale = transform.GetScale();
			sf::Vector2f origin = transform.GetOrigin();

			if (ImGui::TreeNodeEx("TransformComponent1", treeFlag, "Translate"))
			{
				if (VegaUI::DrawControl2("Translate", translate, 1.0f, 1.0f))
					transform.SetTranslate(translate);
				if (VegaUI::DrawControl2("Scale", scale, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f))
					transform.SetScale(scale);
				if (VegaUI::DrawControl1("Rotation", "Z", rotation, 1.0f, 0.0f, 360.f, 0.0f))
					transform.SetRotation(rotation);
				ImGui::TreePop();

			}
		}

		if (entity.HasComponent<CameraComponent>())
		{
			if (ImGui::TreeNodeEx("CameraComponent", treeFlag, "Camera"))
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
			if (ImGui::TreeNodeEx("SpriteComponent", treeFlag, "Sprite"))
			{
				SpriteComponent& spriteComp = entity.GetComponent<SpriteComponent>();
				sf::Sprite& sprite = spriteComp.Sprite;
				sf::Color color = sprite.getColor();
				if (VegaUI::ColorEdit4(color, "Color"))
				{
					sprite.setColor(color);
				}
				ImGui::TreePop();
			}
		}
	}

} // namespace fz