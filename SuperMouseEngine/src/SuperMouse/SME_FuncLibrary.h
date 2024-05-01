#pragma once

#include <random>
#include <glm/glm.hpp>

namespace super_mouse
{
    template <typename T>
    T clamp(T value, T min, T max)
    {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }

    inline int getRandomInt(const int min, const int max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

    inline double getTimeMilliseconds()
    {
        using namespace std::chrono;
        const high_resolution_clock::time_point now = high_resolution_clock::now();
        const duration<double, std::milli> timeSpan = duration_cast<duration<double, std::milli>>(now.time_since_epoch());
        return timeSpan.count();
    }

    template <typename T>
    void addUnique(const T& newItem, std::vector<T>& array)
    {
        if (!std::any_of(array.begin(), array.end(), [newItem](const T& elem) { return newItem == elem; }))
        {
            array.push_back(newItem);
        }
    }

    inline void sortVec2Y(std::vector<glm::ivec2>& array)
    {
        std::sort(array.begin(), array.end(), [](const glm::ivec2& a, const glm::ivec2& b) { return a.y > b.y; });
    }

}  // namespace super_mouse
