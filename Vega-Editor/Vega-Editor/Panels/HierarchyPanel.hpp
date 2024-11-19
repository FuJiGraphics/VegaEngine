
namespace fz {

	template<typename T>
	void HierarchyPanel::DisplayAddComponentEntry(const std::string& entryName)
	{
		if (!m_SelectionContext.HasComponent<T>())
		{
			if (ImGui::MenuItem(entryName.c_str()))
			{
				m_SelectionContext.AddComponent<T>();
				if (std::is_same<T, CameraComponent>().value)
				{
					sf::Vector2f pos;
					if (m_SelectionContext.HasComponent<SpriteComponent>())
					{
						TransformComponent& transformComp = m_SelectionContext.GetComponent<TransformComponent>();
						pos = transformComp.Transform.GetTranslate();
					}
					CameraComponent& cameraComp = m_SelectionContext.GetComponent<CameraComponent>();
					cameraComp.Camera.SetCenter(pos);
					cameraComp.Camera.SetSize(FRAMEWORK.GetWidth(), FRAMEWORK.GetHeight());
				}
				if (std::is_same<T, RigidbodyComponent>().value)
				{
					// TODO: 임시 물리
					m_Context->StartPhysics();
				}
				ImGui::CloseCurrentPopup();
			}
		}
	}

} // namespace fz