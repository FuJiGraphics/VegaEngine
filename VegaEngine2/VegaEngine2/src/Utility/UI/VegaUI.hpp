#pragma once
#include <imgui.h>

namespace fz {
	
	class VegaUI 
	{
	public:
		static bool ColorEdit4(sf::Color& dst, const std::string& label, bool isRightLabel = false)
		{
			const char* newLabel = "##Empty";
			if (!label.empty())
			{
				if (isRightLabel)
					newLabel = label.c_str();
				else
					newLabel = VegaUI::LabelPrefix(label);
			}
			
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


	};

} // namespace fz
