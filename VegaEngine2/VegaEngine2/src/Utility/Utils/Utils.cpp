#include "pch.h"
#include "Utils.h"

namespace fz {

    namespace {
        const double s_Pi = std::atan(1) * 4;
    }

    sf::Vector2f Utils::SetOrigin(sf::Transformable& obj, Origins preset, const sf::FloatRect& rect)
    {
        sf::Vector2f newOrigin(rect.width, rect.height);
        newOrigin.x *= ((int)preset % 3) * 0.5f;
        newOrigin.y *= ((int)preset / 3) * 0.5f;
        obj.setOrigin(newOrigin);
        return newOrigin;
    }

    sf::Vector2f Utils::SetOrigin(sf::Sprite& obj, Origins preset)
    {
        return Utils::SetOrigin(obj, preset, obj.getLocalBounds());
    }

    sf::Vector2f Utils::SetOrigin(sf::RectangleShape& obj, Origins preset)
    {
        return Utils::SetOrigin(obj, preset, obj.getLocalBounds());
    }

    sf::Vector2f Utils::SetOrigin(sf::Vector2f& vec2, Origins preset, const sf::Vector2f& size)
    {
		sf::Vector2f newOrigin(size.x, size.y);
		newOrigin.x *= ((int)preset % 3) * 0.5f;
		newOrigin.y *= ((int)preset / 3) * 0.5f;
        vec2 = newOrigin;
        return newOrigin;
    }

    float Utils::Clamp(float value, float min, float max)
    {
        if (value < min)
            return min;
        if (value > max)
            return max;
        return value;
    }

    float Utils::Clamp01(float value)
    {
        return Clamp(value, 0.f, 1.f);
    }

    float Utils::Lerp(float min, float max, float t, bool clamp)
    {
        if (clamp)
            t = Clamp01(t);
        return min + (max - min) * t;
    }

    sf::Vector2f Utils::Lerp(const sf::Vector2f& min, const sf::Vector2f& max, float t, bool clamp)
    {
        if (clamp)
            t = Clamp01(t);
        return min + (max - min) * t;
    }

    sf::Color Utils::Lerp(const sf::Color& min, const sf::Color& max, float t, bool clamp)
    {
        if (clamp)
            t = Clamp01(t);

        return sf::Color(
            (sf::Uint8)Lerp(min.r, max.r, t, clamp),
            (sf::Uint8)Lerp(min.g, max.g, t, clamp),
            (sf::Uint8)Lerp(min.b, max.b, t, clamp),
            (sf::Uint8)Lerp(min.a, max.a, t, clamp)
        );
    }

    float Utils::SqrMagnitude(const sf::Vector2f& vec)
    {
        return vec.x * vec.x + vec.y * vec.y;
    }

    float Utils::Magnitude(const sf::Vector2f& vec)
    {
        return std::sqrtf(SqrMagnitude(vec));
    }

    void Utils::Normalize(sf::Vector2f& vec)
    {
        float mag = Magnitude(vec);
        if (mag != 0)
            vec /= mag;
    }

    sf::Vector2f Utils::GetNormal(const sf::Vector2f& vec)
    {
        float mag = Magnitude(vec);
        if (mag != 0)
            return vec;
        return vec / mag;
    }

    float Utils::Distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
    {
        return Magnitude(p2 - p1);
    }

    float Utils::RadianToDegree(float radian)
    {
        return radian * (180.f / Utils::GetPi());
    }

    float Utils::DegreeToRadian(float degree)
    {
        return degree * (Utils::GetPi() / 180.f);
    }

    float Utils::AngleRadian(const sf::Vector2f& vec)
    {
        return std::atan2(vec.y, vec.x);
    }

    float Utils::Angle(const sf::Vector2f& vec)
    {
        return RadianToDegree(AngleRadian(vec));
    }

    float Utils::GetAngleToCos(float degree)
    {
        return cosf(DegreeToRadian(degree));
    }

    float Utils::GetAngleToSin(float degree)
    {
        return sinf(DegreeToRadian(degree));
    }

    sf::Vector2f Utils::GetRotateVector(float angle, const sf::Vector2f& target)
    {
        sf::Transform rotMat = sf::Transform::Identity;
        rotMat.rotate(angle);
        sf::Vector2f v = rotMat * target;
        Utils::Normalize(v);
        return v;
    }

    const double Utils::GetPi()
    {
        return s_Pi;
    }

    bool Utils::CanFileOpen(const std::string& path)
    {
		bool result = false;
		std::ifstream file(path);
		if (file.is_open())
		{
			result = true;
		}
		file.close();
		return result;
    }

} // namespace fz

