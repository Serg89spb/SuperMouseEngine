#include "DigitLine.h"

struct FTransformPoint
{
    FTransformPoint(float scale) : scale(scale) {}
    FTransformPoint(float scale, float offsetX, float offsetY) : scale(scale), offsetX(offsetX), offsetY(offsetY) {}
    float scale = 1.0f;
    float offsetX = 0.0f;
    float offsetY = 0.0f;
};

namespace super_mouse
{
    std::map<EDigitLineType, std::vector<SDL_FPoint>> linePointsMap{//
        {upLeft,{//
            {SDL_FPoint({ 0.0f, 0.2f})},//
            {SDL_FPoint({ 0.9f, 1.1f})},//
            {SDL_FPoint({ 0.9f, 4.1f})},//
            {SDL_FPoint({ 0.9f, 4.1f})},//
            {SDL_FPoint({ 0.0f, 5.1f})},//
            {SDL_FPoint({ 0.0f, 0.2f})},//
        }},//
        {upTop,{//
            {SDL_FPoint({ 0.2f, 0.0f})},//
            {SDL_FPoint({ 4.1f, 0.0f})},//
            {SDL_FPoint({ 3.1f, 0.9f})},//
            {SDL_FPoint({ 3.1f, 0.9f})},//
            {SDL_FPoint({ 1.1f, 0.9f})},//
            {SDL_FPoint({ 0.2f, 0.0f})},//
        }},//
        {upRight,{//
            {SDL_FPoint({ 3.3f, 1.1f})},//
            {SDL_FPoint({ 4.2f, 0.2f})},//
            {SDL_FPoint({ 4.2f, 5.1f})},//
            {SDL_FPoint({ 4.2f, 5.1f})},//
            {SDL_FPoint({ 3.3f, 4.1f})},//
            {SDL_FPoint({ 3.3f, 1.1f})},//
        }},//
        {center,{//
            {SDL_FPoint({ 0.2f, 5.3f})},//
            {SDL_FPoint({ 1.1f, 4.8f})},//
            {SDL_FPoint({ 3.1f, 4.8f})},//
            {SDL_FPoint({ 3.1f, 4.8f})},//
            {SDL_FPoint({ 4.1f, 5.3f})},//
            {SDL_FPoint({ 0.2f, 5.3f})},//
            //
            {SDL_FPoint({ 0.2f, 5.3f})},//
            {SDL_FPoint({ 4.1f, 5.3f})},//
            {SDL_FPoint({ 3.1f, 5.8f})},//
            {SDL_FPoint({ 3.1f, 5.8f})},//
            {SDL_FPoint({ 1.1f, 5.8f})},//
            {SDL_FPoint({ 0.2f, 5.3f})},//
        }},//
        {bottomLeft,{//
            {SDL_FPoint({ 0.0f, 5.5f})},//
            {SDL_FPoint({ 0.9f, 6.4f})},//
            {SDL_FPoint({ 0.9f, 9.4f})},//
            {SDL_FPoint({ 0.9f, 9.4f})},//
            {SDL_FPoint({ 0.0f, 10.4f})},//
            {SDL_FPoint({ 0.0f, 5.5f})},//
        }},//
        {bottomDown,{//
            {SDL_FPoint({ 0.2f, 10.6f})},//
            {SDL_FPoint({ 1.1f, 9.5f})},//
            {SDL_FPoint({ 3.1f, 9.5f})},//
            {SDL_FPoint({ 3.1f, 9.5f})},//
            {SDL_FPoint({ 4.1f, 10.6f})},//
            {SDL_FPoint({ 0.2f, 10.6f})},//
        }},//
        {bottomRight,{//
            {SDL_FPoint({ 3.3f, 6.4f})},//
            {SDL_FPoint({ 4.2f, 5.5f})},//
            {SDL_FPoint({ 4.2f, 10.4f})},//
            {SDL_FPoint({ 4.2f, 10.4f})},//
            {SDL_FPoint({ 3.3f, 9.4f})},//
            {SDL_FPoint({ 3.3f, 6.4f})},//
        }},//

    };

    DigitLine::DigitLine(EDigitLineType line, glm::vec2 pos, float scale) : _currentLine(line), _pos(pos), _scale(scale)
    {
    }

    void DigitLine::render(SDL_Renderer* renderer)
    {
        drawDigitLine(renderer);
    }

    void DigitLine::drawDigitLine(SDL_Renderer* renderer)
    {
        if (_currentLine == center)
        {
            constexpr int size = 12;
            SDL_Vertex vertices[size];
            makeVertices(linePointsMap[_currentLine], FTransformPoint(_scale, _pos.x, _pos.y), vertices);
            SDL_RenderGeometry(renderer, nullptr, vertices, size, {}, 0);
            return;
        }

        constexpr int size = 6;
        SDL_Vertex vertices[size];
        makeVertices(linePointsMap[_currentLine], FTransformPoint(_scale, _pos.x, _pos.y), vertices);
        SDL_RenderGeometry(renderer, nullptr, vertices, size, {}, 0);
    }

    void DigitLine::makeVertices(const std::vector<SDL_FPoint>& points, FTransformPoint transform, SDL_Vertex* vertices)
    {
        auto clr = Color::fill;
        const auto sdlClr = SDL_Color({ clr.r, clr.b, clr.g, clr.a });

        for (int i = 0; i < (int)points.size(); ++i)
        {
            const auto point = transformPoint(points[i], transform);
            vertices[i] = SDL_Vertex({ point, sdlClr,{} });
        }
    }

    SDL_FPoint DigitLine::transformPoint(const SDL_FPoint& point, FTransformPoint transform)
    {
        return SDL_FPoint({ point.x * transform.scale + transform.offsetX, point.y * transform.scale + transform.offsetY });
    }
}
