
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
						SpriteComponent& spriteComp = m_SelectionContext.GetComponent<SpriteComponent>();
						sf::Sprite& sprite = spriteComp.Sprite;
						pos = sprite.getPosition();
					}
					CameraComponent& cameraComp = m_SelectionContext.GetComponent<CameraComponent>();
					cameraComp.Camera.SetCenter(pos);
					cameraComp.Camera.SetSize(FRAMEWORK.GetWidth(), FRAMEWORK.GetHeight());
				}
				ImGui::CloseCurrentPopup();
			}
		}
	}

} // namespace fz