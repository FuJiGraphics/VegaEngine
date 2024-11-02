#include "pch.h"
#include "Random.h"
#include <random>
#include <cmath>

namespace fz {

    const float Random_internal::s_PI = 3.1415926f;

    Random_internal& Random_internal::GetInstance()
    {
        static Random_internal s_Ran;
        return s_Ran;
    }

    int Random_internal::operator()(int min, int max) const
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(min, max);
        return (dis(gen));
    }

    float Random_internal::operator()(float min, float max) const
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(min, max);
        return (dis(gen));
    }

    bool Random_internal::Boolean() const
    {
        int result = (*this)(0, 1);
        return (result) ? true : false;
    }

    sf::Vector2f Random_internal::InUnitCircle() const
    {
        float angle = Random(0.f, 2.f * s_PI);
        return { std::cosf(angle), std::sinf(angle) };
    }

    sf::Vector2f Random_internal::InUnitCircle()
    {
        float angle = Random(0.f, 2.f * s_PI);
        return { std::cosf(angle), std::sinf(angle) };
    }

} // namespace fz