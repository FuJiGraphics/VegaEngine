#include "pch.h"
#include "VegaUI.h"

namespace fz {
	bool VegaUI::DrawControl1(const std::string& label,
							  const std::string& buttonLabel,
							  float& v,
							  float speed_x, float x_min, float x_max,
							  float resetValue, float columnWidth)
	{
		bool result = false;
		ImGui::PushID(label.c_str());
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);

		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 4.f });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight * 1.81f, lineHeight };

		ImGui::PushMultiItemsWidths(1, ImGui::CalcItemWidth());
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.3f, 0.3f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.4f, 0.4f, 0.4f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.3f, 0.3f, 0.3f, 1.0f });
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

	bool VegaUI::DrawControl2(const std::string& label, sf::Vector2f& vec2,
									 float speed_x, float speed_y,
									 float x_min, float x_max,
									 float y_min, float y_max,
									 float resetValue, float columnWidth)
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

		ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
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


	bool VegaUI::ColorEdit4(sf::Color& dst, const std::string& label)
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

	bool VegaUI::ColorEdit4WidthCheckbox(sf::Color& dst, bool& check, const std::string& label)
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
			if (check)
				result = true;
		}

		ImGui::SameLine();
		if (ImGui::Checkbox("##Mask", &check))
		{
			result = true;
		}
		ImGui::PopStyleVar();
		ImGui::Columns(1);

		ImGui::PopID();
		return result;
	}

	bool VegaUI::InputText(std::string& dst, const std::string& label, bool isRightLabel)
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

	bool VegaUI::InputFloat(float& dst, const std::string& label, bool isRightLabel, float step, float step_fast)
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

	bool VegaUI::InputFloat2(sf::Vector2f& dst, const std::string& label, bool isRightLabel)
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

	bool VegaUI::DragFloat(float& dst, const std::string& label, bool isRightLabel, float v_speed, float v_min, float v_max)
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

	bool VegaUI::DragFloat2(sf::Vector2f& dst, const std::string& label, bool isRightLabel, float v_speed, float v_min, float v_max)
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

	bool VegaUI::DragFloat4(sf::FloatRect& dst, const std::string& label, bool isRightLabel, float v_speed, float v_min, float v_max)
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

	const char* VegaUI::LabelPrefix(const std::string& label)
	{
		ImGui::Text(label.c_str());
		ImGui::SameLine();

		static std::string labelID = "";
		labelID = "##" + label;

		return labelID.c_str();
	}

	void VegaUI::SelectOrigins(fz::Sprite& sprite, float columnWidth)
	{
		ImGui::PushID("Origins");
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text("Origins");
		ImGui::NextColumn();

		const char* items[] = { "Custom", "TopLeft", "TopCenter", "TopRight", "MidLeft", "MidCenter", "MidRight", "BotLeft", "BotCenter", "BotRight" };
		Origins item_selected_origins = sprite.GetOrigins();

		int preview = (item_selected_origins == Origins::Custom) ? 0 : (int)(item_selected_origins)+1;
		const char* combo_preview_value = items[preview];
		if (ImGui::BeginCombo("##Origins", combo_preview_value))
		{
			for (int n = 0; n < IM_ARRAYSIZE(items); n++)
			{
				bool is_selected = false;
				if (ImGui::Selectable(items[n], is_selected))
				{
					item_selected_origins = (n == 0) ? Origins::Custom : (Origins)(n - 1);
					is_selected = true;
				}

				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
					sprite.SetOrigins(item_selected_origins);
				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
		ImGui::Columns(1);
		ImGui::PopID();
	}

	bool VegaUI::PopupContextItem(const std::string& item, const std::function<void()>& fn)
	{
		bool result = false;
		if (ImGui::BeginPopupContextItem(0, ImGuiPopupFlags_MouseButtonRight))
		{
			if (ImGui::MenuItem(item.c_str()))
			{
				fn();
				result = true;
			}
			ImGui::EndPopup();
		}
		return result;
	}

} // namespace fz