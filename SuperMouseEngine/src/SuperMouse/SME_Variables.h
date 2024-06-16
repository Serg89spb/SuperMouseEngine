#pragma once

namespace super_mouse
{
    constexpr int unit = 32;
    constexpr int fps_limit = 60;

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
        bool pause = false;
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

    enum EDigitLineType
    {
        upLeft,
        upTop,
        upRight,
        center,
        bottomLeft,
        bottomDown,
        bottomRight
    };

    enum ERightBarText
    {
        Hi,
        Score,
        Speed,
        Level,
        Pause,
        GameOver
    };

}  // namespace super_mouse
