#pragma once
#include <imgui.h>
#include <imgui_internal.h>

namespace fz {
	
	class VegaUI 
	{
	public:
		static bool DrawControl1(const std::string& label, const std::string& buttonLabel,
								 float& v,
								 float speed_x = 0.1f, 
								 float x_min = 0.0f, float x_max = 0.0f,
								 float resetValue = 0.0f, float columnWidth = 100.f)
		{
			bool result = false;
			ImGui::PushID(label.c_str());
			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, columnWidth);

			ImGui::Text(label.c_str());
			ImGui::NextColumn();

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImVec2 buttonSize = { lineHeight, lineHeight };

			ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			if (ImGui::Button(buttonLabel.c_str(), buttonSize))
			{
				v = resetValue;
				result = true;
			}
			ImGui::PopStyleColor(3);
			ImGui::SameLine();
			if (ImGui::DragFloat("##y", &v, speed_x, x_min, x_max))
				result = true;
			ImGui::PopItemWidth();

			ImGui::PopStyleVar();
			ImGui::Columns(1);

			ImGui::PopID();
			return result;
		}

		static bool DrawControl2(const std::string& label, sf::Vector2f& vec2,
								 float speed_x = 0.1f, float speed_y = 0.1f,
								 float x_min = 0.0f, float x_max = 0.0f,
								 float y_min = 0.0f, float y_max = 0.0f,
								 float resetValue = 0.0f, float columnWidth = 100.f)
		{
			bool result = false;
			ImGui::PushID(label.c_str());
			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, columnWidth);

			ImGui::Text(label.c_str());
			ImGui::NextColumn();
						
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImVec2 buttonSize = { lineHeight, lineHeight };

			ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
			if (ImGui::Button("X", buttonSize))
			{
				vec2.x = resetValue;
				result = true;
			}
			ImGui::PopStyleColor(3);
			ImGui::SameLine();
			if (ImGui::DragFloat("##x", &vec2.x, speed_x, x_min, x_max))
				result = true;
			ImGui::PopItemWidth();
			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
			if (ImGui::Button("Y", buttonSize))
			{
				vec2.y = resetValue;
				result = true;
			}
			ImGui::PopStyleColor(3);
			ImGui::SameLine();
			if (ImGui::DragFloat("##y", &vec2.y, speed_y, y_min, y_max))
				result = true;
			ImGui::PopItemWidth();

			ImGui::PopStyleVar();
			ImGui::Columns(1);

			ImGui::PopID();
			return result;
		}

		static bool ColorEdit4(sf::Color& dst, const std::string& label)
		{
			const char* newLabel = "##Empty";

			ImGui::PushID(label.c_str());
			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, 100.f);

			ImGui::Text(label.c_str());
			ImGui::NextColumn();

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
			// rect 초기화
			auto& [r, g, b, a] = dst;  // dst가 sf::Color라고 가정
			std::vector<float> rect(4, 0.0f);
			rect[0] = r / 255.0f;
			rect[1] = g / 255.0f;
			rect[2] = b / 255.0f;
			rect[3] = a / 255.0f;

			bool result = false;
			if (ImGui::ColorEdit4(newLabel, rect.data()))
			{
				r = (sf::Uint8)(rect[0] * 255);
				g = (sf::Uint8)(rect[1] * 255);
				b = (sf::Uint8)(rect[2] * 255);
				a = (sf::Uint8)(rect[3] * 255);
				result = true;
			}

			ImGui::PopStyleVar();
			ImGui::Columns(1);

			ImGui::PopID();
			return result;
		}
		static bool InputText(std::string& dst, const std::string& label = "", bool isRightLabel = false)
		{
			const char* newLabel = "##Empty";
			if (!label.empty())
			{
				if (isRightLabel)
					newLabel = label.c_str();
				else
					newLabel = VegaUI::LabelPrefix(label);
			}

			char buf[256];
			memset(buf, '\0', sizeof(buf));
			memcpy_s(buf, sizeof(buf), dst.c_str(), dst.size());

			bool result = false;
			if (ImGui::InputText(newLabel, buf, sizeof(buf)))
			{
				dst = buf;
				result = true;
			}

			return result;
		}
		static bool InputFloat(float& dst, const std::string& label = "", bool isRightLabel = false, float step = 0.0f, float step_fast = 0.0f)
		{
			float f = 0.0f;
			f = dst;

			const char* newLabel = "##Empty";
			if (!label.empty())
			{
				if (isRightLabel)
					newLabel = label.c_str();
				else
					newLabel = VegaUI::LabelPrefix(label);
			}

			bool result = false;
			if (ImGui::InputFloat(newLabel, &f, step, step_fast))
			{
				dst = f;
				result = true;
			}
			return result;
		}
		static bool InputFloat2(sf::Vector2f& dst, const std::string& label = "", bool isRightLabel = false)
		{
			float f[2] = { 0.0f, 0.0f };
			f[0] = dst.x;
			f[1] = dst.y;

			const char* newLabel = "##Empty";
			if (!label.empty())
			{
				if (isRightLabel)
					newLabel = label.c_str();
				else
					newLabel = VegaUI::LabelPrefix(label);
			}

			bool result = false;
			if (ImGui::InputFloat2(newLabel, f))
			{
				dst.x = f[0];
				dst.y = f[1];
				result = true;
			}
			return result;
		}
		static bool DragFloat(float& dst, const std::string& label = "", bool isRightLabel = false, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f)
		{
			float f = 0.0f;
			f = dst;

			const char* newLabel = "##Empty";
			if (!label.empty())
			{
				if (isRightLabel)
					newLabel = label.c_str();
				else
					newLabel = VegaUI::LabelPrefix(label);
			}

			bool result = false;
			if (ImGui::DragFloat(newLabel, &f, v_speed, v_min, v_max))
			{
				dst = f;
				result = true;
			}
			return result;
		}
		static bool DragFloat2(sf::Vector2f& dst, const std::string& label = "", bool isRightLabel = false, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f)
		{
			float f[2] = { 0.0f, 0.0f };
			f[0] = dst.x;
			f[1] = dst.y;

			const char* newLabel = "##Empty";
			if (!label.empty())
			{
				if (isRightLabel)
					newLabel = label.c_str();
				else
					newLabel = VegaUI::LabelPrefix(label);
			}

			bool result = false;
			if (ImGui::DragFloat2(newLabel, f, v_speed, v_min, v_max))
			{
				dst.x = f[0];
				dst.y = f[1];
				result = true;
			}
			return result;
		}
		static bool DragFloat4(sf::FloatRect& dst, const std::string& label = "", bool isRightLabel = false, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f)
		{
			float f[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			f[0] = dst.left;
			f[1] = dst.top;
			f[2] = dst.width;
			f[3] = dst.height;
			const char* newLabel = "##Empty";
			if (!label.empty())
			{
				if (isRightLabel)
					newLabel = label.c_str();
				else
					newLabel = VegaUI::LabelPrefix(label);
			}

			bool result = false;
			if (ImGui::DragFloat4(newLabel, f, v_speed, v_min, v_max))
			{
				dst.left = f[0];
				dst.top = f[1];
				dst.width = f[2];
				dst.height = f[3];
				result = true;
			}
			return result;
		}
		static const char* LabelPrefix(const std::string& label)
		{
			ImGui::Text(label.c_str());
			ImGui::SameLine();

			static std::string labelID = "";
			labelID = "##" + label;

			return labelID.c_str();
		}
		static std::string OpenFile(HWND hwnd, const char* filter)
		{
			OPENFILENAMEA ofn;
			CHAR szFile[260] = { 0 };
			CHAR currentDir[256] = { 0 };
			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			if (GetCurrentDirectoryA(256, currentDir))
				ofn.lpstrInitialDir = currentDir;
			ofn.lpstrFilter = filter;
			ofn.nFilterIndex = 1;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

			if (GetOpenFileNameA(&ofn) == TRUE)
				return ofn.lpstrFile;

			return std::string();

		}

		static std::string SaveFile(HWND hwnd, const char* filter)
		{
			OPENFILENAMEA ofn;
			CHAR szFile[260] = { 0 };
			CHAR currentDir[256] = { 0 };
			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			if (GetCurrentDirectoryA(256, currentDir))
				ofn.lpstrInitialDir = currentDir;
			ofn.lpstrFilter = filter;
			ofn.nFilterIndex = 1;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

			// Sets the default extension by extracting it from the filter
			ofn.lpstrDefExt = strchr(filter, '\0') + 1;

			if (GetSaveFileNameA(&ofn) == TRUE)
				return ofn.lpstrFile;

			return std::string();
		}
	};

} // namespace fz
