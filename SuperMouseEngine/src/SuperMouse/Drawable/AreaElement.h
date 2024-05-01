#pragma once
#include "Drawable.h"

namespace super_mouse
{

    class AreaElement final : public Drawable
    {
    public:
        AreaElement();
        void render(SDL_Renderer* renderer) override;

    private:
        std::vector<SDL_Rect> _rects;
    };

}  // namespace super_mouse


