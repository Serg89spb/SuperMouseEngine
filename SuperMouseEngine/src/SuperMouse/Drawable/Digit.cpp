#include "Digit.h"

namespace super_mouse
{
    std::vector<std::vector<EDigitLineType>> digitsLines{//
        {upLeft,//
         upTop,//
         upRight,//
         bottomLeft,//
         bottomDown,//
         bottomRight//
        },//0
        {upRight,//
         bottomRight//
        },//1
        {upTop,
         upRight,
         center,
         bottomLeft,
         bottomDown,
        },//2
        {upTop,
         upRight,
         center,
         bottomDown,
         bottomRight
        },//3
        {upLeft,
         upRight,
         center,
         bottomRight
        },//4
        {upLeft,
         upTop,
         center,
         bottomDown,
         bottomRight
        },//5
        {upLeft,
         upTop,
         center,
         bottomLeft,
         bottomDown,
         bottomRight
        },//6
        {upTop,
         upRight,
         bottomRight
        },//7
        {upLeft,
         upTop,
         upRight,
         center,
         bottomLeft,
         bottomDown,
         bottomRight
        },//8
        {upLeft,
         upTop,
         upRight,
         center,
         bottomDown,
         bottomRight
        },//9

    };

    Digit::Digit()
    {
    }

    Digit::Digit(int digit, glm::vec2 pos, float scale) : _currentDigit(digit)
    {
        for (const auto& eline : digitsLines[digit])
        {
            _lines.push_back(DigitLine(eline, pos, scale));
        }
    }

    void Digit::render(SDL_Renderer* renderer)
    {
        drawDigit(_currentDigit, renderer);
    }

    void Digit::drawDigit(int digit, SDL_Renderer* renderer)
    {
        for (auto& line : _lines)
        {
            line.drawDigitLine(renderer);
        }

    }
}
