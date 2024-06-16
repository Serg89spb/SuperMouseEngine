#include "Drawable.h"

namespace super_mouse
{
    void Drawable::render(SDL_Renderer* renderer)
    {
        if (isBlinking())
        {
            frameCounter++;
            if ((float)frameCounter / (float)fps_limit > _blinkingPeriod)
            {
                toggleVisibility();
                frameCounter = 0;
            }
        }
    }

    void Drawable::setIsBlinking(bool isBlink)
    {
        _isBlinking = isBlink;
        frameCounter = 0;
        if (isBlink)
        {
            _savedVisible = _visible;
        }
        else
        {
            _visible = _savedVisible;
        }
    }

    void Drawable::toggleVisibility()
    {
        _visible = !_visible;
    }
}
