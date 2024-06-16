#include "NumberBox.h"

namespace super_mouse
{
    NumberBox::NumberBox(int cellNum, glm::vec2 pos, float numberScale) : _digits({}), _cellNum(cellNum), _pos(pos), _numberScale(numberScale)
    {
    }

    void NumberBox::render(SDL_Renderer* renderer)
    {
        Drawable::render(renderer);

        if (!visibility()) return;
        for (auto& dig : _digits)
        {
            dig.render(renderer);
        }
    }

    void NumberBox::setNumber(int number)
    {
        _number = number;
        std::vector<int> array = numberArray(number);
        int size = (int)array.size();

        CHECK(size <= _cellNum, "size cannot be grather then _cellNum");

        _digits.clear();
        _digits.resize(size);

        for (int i = 0; i < size; ++i)
        {
            _digits[i] = Digit(array[i], { _pos.x + ((float)_cellNum - (float)(size - i)) * _numberScale * 7.0f,_pos.y }, _numberScale);
        }
    }

    std::vector<int> NumberBox::numberArray(const int number)
    {
        std::vector<int> array;

        int modNumber = number;
        bool isZero = modNumber / 10 == 0;
        while (!isZero)
        {
            array.insert(array.begin(), modNumber % 10);
            modNumber /= 10;
            isZero = modNumber / 10 == 0;
        }
        if (isZero)
        {
            array.insert(array.begin(), modNumber);
        }
        return array;
    }
}
