#pragma once
#include <SDL_render.h>
#include "SME_Core.h"

namespace super_mouse
{
    class Drawable
    {
    public:
        virtual ~Drawable() = default;
        virtual void render(SDL_Renderer* renderer) = 0;
    };

}  // namespace super_mouse


