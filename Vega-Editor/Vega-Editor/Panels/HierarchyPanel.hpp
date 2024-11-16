
namespace fz {

	template<typename T>
	void HierarchyPanel::DisplayAddComponentEntry(const std::string& entryName)
	{
		if (!m_SelectionContext.HasComponent<T>())
		{
			if (ImGui::MenuItem(entryName.c_str()))
			{
				m_SelectionContext.AddComponent<T>();
				ImGui::CloseCurrentPopup();
			}
		}
	}

} // namespace fz