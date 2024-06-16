#pragma once
#include "Drawable.h"

namespace super_mouse
{
    class DrawableText : public Drawable
    {
    public:
        DrawableText(const std::string&& text, int fontScale, glm::ivec2 pos);

        void render(SDL_Renderer* renderer) override;

    private:
        std::string _text;
        int _fontScale;
        glm::ivec2 _pos;
    };
}
