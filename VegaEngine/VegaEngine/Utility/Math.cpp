#include "Core/stdafx.h"
#include "Math.h"
#include <random>

namespace fz {

    int Utils::GetRandom(int start, int end)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(start, end);
        return (dis(gen));
    }

}