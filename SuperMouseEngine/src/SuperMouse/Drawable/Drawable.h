#pragma once
#include <SDL_render.h>
#include "SME_Core.h"

namespace super_mouse
{
    class Drawable
    {
    public:
        virtual ~Drawable() = default;
        virtual void render(SDL_Renderer* renderer);

        void setVisibility(bool visible) { _visible = visible; }
        bool visibility() const { return _visible; }

        void setIsBlinking(bool isBlink);
        void setBlinkingPeriod(float period) { _blinkingPeriod = period; }

        bool isBlinking() const { return _isBlinking; }
        float blinkingPeriod() const { return _blinkingPeriod; }

    private:
        bool _visible = true;
        bool _isBlinking = false;
        float _blinkingPeriod = 0.5f;

        bool _savedVisible = true;
        int frameCounter = 0;

        void toggleVisibility();

    };

}  // namespace super_mouse


