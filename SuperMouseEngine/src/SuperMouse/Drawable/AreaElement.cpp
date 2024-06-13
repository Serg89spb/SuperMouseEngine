#include "AreaElement.h"
#include "SME_Core.h"

namespace super_mouse
{
    namespace frame
    {
        const glm::ivec2 loc_hor1 = { 4, 21 * unit + 8 };
        const glm::ivec2 loc_hor2 = { 4, 8 };
        const glm::ivec2 size_hor = { 10 * unit - 8, 4 };

        const glm::ivec2 loc_vert = { 10 * unit + 8, 16 };
        const glm::ivec2 size_ver = { 4, 21 * unit - 8 };
    }  // namespace frame

    //AreaElement()

    // GridBorder
    AreaElement::AreaElement()
    {
        _rects.resize(3);
        _rects[0] = { frame::loc_hor1.x, frame::loc_hor1.y, frame::size_hor.x, frame::size_hor.y };
        _rects[1] = { frame::loc_hor2.x, frame::loc_hor2.y, frame::size_hor.x, frame::size_hor.y };
        _rects[2] = { frame::loc_vert.x, frame::loc_vert.y, frame::size_ver.x, frame::size_ver.y };
    }

    void AreaElement::render(SDL_Renderer* renderer)
    {
        for (const auto& rect : _rects)
        {
            const auto fl = Color::fill;
            SDL_SetRenderDrawColor(renderer, fl.r, fl.g, fl.b, fl.a);
            SDL_RenderFillRect(renderer, &rect);
        }
    }

}  // namespace super_mouse
