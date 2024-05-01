#include "Brick.h"

namespace super_mouse
{
    namespace
    {
        glm::ivec2 size = { unit, unit };
        constexpr int offset1 = 1;
        constexpr int offset2 = 3;
        constexpr int offset3 = 6;
    }  // namespace

    Brick::Brick()
    {
        _rects.resize(4);
    }

    void Brick::setWorldLocation(const glm::ivec2& location)
    {
        _worldLocation = location;
        setRectsLoc(_worldLocation * unit);
    }

    void Brick::setRelLocation(const glm::ivec2& location)
    {
        _relLocation = location;
        setRectsLoc(_worldLocation * unit);
    }

    void Brick::setRectsLoc(const glm::ivec2& location)
    {
        _rects[0] = { location.x, location.y, size.x, size.y };
        _rects[1] = { location.x + offset1, location.y + offset1, size.x - offset1 * 2, size.y - offset1 * 2 };
        _rects[2] = { location.x + offset2, location.y + offset2, size.x - offset2 * 2, size.y - offset2 * 2 };
        _rects[3] = { location.x + offset3, location.y + offset3, size.x - offset3 * 2, size.y - offset3 * 2 };
    }

    void Brick::render(SDL_Renderer* renderer)
    {
        bool renderRect = true;
        // TODO
        if (_worldLocation.x < game_field::min_x || _worldLocation.x > game_field::max_x ||  //
            _worldLocation.y < game_field::min_y || _worldLocation.y > game_field::max_y)    //
        {
            renderRect = false;
        }

        if (renderRect)
        {
            bool isBgColor = true;
            for (const auto& rect : _rects)
            {
                const auto clr = isBgColor ? Color::background : Color::fill;
                SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);
                SDL_RenderFillRect(renderer, &rect);
                isBgColor = !isBgColor;
            }
        }
    }
}  // namespace super_mouse
