#pragma once
#include <imgui.h>

namespace fz {
	
	class VegaUI 
	{
	public:
		/*
		* @brief ImGui::InputText�� Left Labeling�� �߰��� ���� �Լ� �Դϴ�.  
		*/
		static bool InputText(const std::string& label, std::string& dst, bool isRightLabel = false)
		{
			bool result = false;

			const char* newLabel = "Null";
			if (isRightLabel)
				newLabel = label.c_str();
			else
				newLabel = VegaUI::LabelPrefix(label);

			char buf[256];
			memset(buf, '\0', sizeof(buf));
			memcpy_s(buf, sizeof(buf), dst.c_str(), dst.size());
			if (ImGui::InputText(newLabel, buf, sizeof(buf)))
			{
				dst = buf;
				result = true;
			}

			return result;
		}

		/*
		* @brief ImGui�� ���� ���� ���̵忡 ��ġ�մϴ�. 
		*/
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
