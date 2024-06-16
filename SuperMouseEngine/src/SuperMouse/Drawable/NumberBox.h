#pragma once
#include "Digit.h"
#include "Drawable.h"

namespace super_mouse
{
    class NumberBox : public Drawable
    {
    public:
        NumberBox(int cellNum, glm::vec2 pos, float numberScale);
        void render(SDL_Renderer* renderer) override;

        void setNumber(int number);
        int number() const { return _number; }

    private:
        int _number = 0;
        std::vector<Digit> _digits;
        int _cellNum;
        glm::vec2 _pos;
        float _numberScale;
        std::vector<int> numberArray(const int number);
    };
}
