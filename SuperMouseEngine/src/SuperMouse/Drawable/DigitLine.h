#pragma once
#include "Drawable.h"

struct FTransformPoint;

namespace super_mouse
{
    class DigitLine : public Drawable
    {
    public:
        DigitLine(EDigitLineType line, glm::vec2 pos, float scale);
        void render(SDL_Renderer* renderer) override;
        void drawDigitLine(SDL_Renderer* renderer);
        void makeVertices(const std::vector<SDL_FPoint>& points, FTransformPoint transform, SDL_Vertex* vertices);
        SDL_FPoint transformPoint(const SDL_FPoint& point, FTransformPoint transform);

    private:
        EDigitLineType _currentLine = upLeft;
        glm::vec2 _pos{};
        float _scale = 1.0f;
    };
}
