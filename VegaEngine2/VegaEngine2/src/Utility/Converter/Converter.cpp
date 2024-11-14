#include "pch.h"

namespace fz {

    MouseButtonType Converter::SfmlToFzType(sf::Mouse::Button button)
    {
        switch (button)
        {
            case sf::Mouse::Left:
                return MouseButtonType::Left;
            case sf::Mouse::Right:
                return MouseButtonType::Right;
            case sf::Mouse::Middle:
                return MouseButtonType::Middle;
            case sf::Mouse::XButton1:
                return MouseButtonType::XButton1;
            case sf::Mouse::XButton2:
                return MouseButtonType::XButton2;
            default:
                FZLOG_ASSERT(false, "타입 변환을 할 수 없습니다. 알 수 없는 타입입니다.");
                break;
        }

        return fz::MouseButtonType();
    }

} // namespace fz