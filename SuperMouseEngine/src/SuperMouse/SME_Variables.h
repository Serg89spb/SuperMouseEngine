#pragma once

namespace super_mouse
{
    constexpr int unit = 32;

    namespace game_field
    {
        constexpr int min_x = 0;
        constexpr int max_x = 9;
        constexpr int min_y = 1;
        constexpr int max_y = 21;
    }  // namespace game_field

    namespace frame
    {
        constexpr int y_offset = 1;
    }

    struct Control
    {
        int offsetX = 0;
        bool needRotate = false;
        bool accelerate = false;

        void reset()
        {
            offsetX = 0;
            needRotate = false;
            accelerate = false;
        }
    };

}  // namespace super_mouse
