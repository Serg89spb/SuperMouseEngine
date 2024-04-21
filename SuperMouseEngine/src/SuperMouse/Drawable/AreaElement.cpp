#include "AreaElement.h"
#include "SME_Core.h"

namespace super_mouse
{
    namespace frame
    {
        const glm::ivec2 loc_hor1 = { 0, 24 * unit };
        const glm::ivec2 loc_hor2 = { 0, y_offset * unit - 2 };
        const glm::ivec2 size_hor = { 10 * unit, 2 };

        const glm::ivec2 loc_vert = { 10 * unit, y_offset * unit };
        const glm::ivec2 size_ver = { 2, 20 * unit };
    }  // namespace frame

    void AreaElement::render(SDL_Renderer* renderer)
    {
        if (!renderer)
        {
            throw std::runtime_error("renderer must be initialized");
        }
        _renderer = renderer;
    }

    void AreaElement::createFrame() const
    {
        std::vector<SDL_Rect> rects;
        rects.push_back({ frame::loc_hor1.x, frame::loc_hor1.y, frame::size_hor.x, frame::size_hor.y });
        rects.push_back({ frame::loc_hor2.x, frame::loc_hor2.y, frame::size_hor.x, frame::size_hor.y });
        rects.push_back({ frame::loc_vert.x, frame::loc_vert.y, frame::size_ver.x, frame::size_ver.y });

        for (const auto& rect : rects)
        {
            SDL_SetRenderDrawColor(_renderer, _fl.r, _fl.g, _fl.b, _fl.a);
            SDL_RenderFillRect(_renderer, &rect);
        }
    }

}  // namespace super_mouse
