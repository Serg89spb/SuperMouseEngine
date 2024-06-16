#pragma once
#include "Drawable.h"
#include "DigitLine.h"

struct FTransformPoint;

namespace super_mouse
{
    class Digit : public Drawable
    {
    public:
        Digit();
        Digit(int digit, glm::vec2 pos, float scale);
        void render(SDL_Renderer* renderer) override;

    private:
        void drawDigit(int digit, SDL_Renderer* renderer);

        int _currentDigit = 0;
        std::vector<DigitLine> _lines;
    };

}
