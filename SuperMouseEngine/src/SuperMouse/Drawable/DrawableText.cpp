#include "DrawableText.h"
#include "SDL_ttf.h"

namespace super_mouse
{
    DrawableText::DrawableText(const std::string&& text, int fontScale, glm::ivec2 pos) : _text(text), _fontScale(fontScale), _pos(pos)
    {
        TTF_Init();
    }

    void DrawableText::render(SDL_Renderer* renderer)
    {
        Drawable::render(renderer);

        if (!visibility()) return;

        std::string file_name = "C:/dev/SuperMouseEngine/SuperMouseEngine/res/imagine_font.ttf";

        TTF_Font* font = TTF_OpenFont(file_name.c_str(), _fontScale);
        TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

        const auto clr = Color::fill;
        SDL_Color sdl_color = { clr.r,clr.g,clr.b };

        int height = 0;
        int width = 0;
        TTF_SizeText(font, _text.c_str(), &height, &width);

        SDL_Surface* surfaceMessage =
            TTF_RenderText_Solid(font, _text.c_str(), sdl_color);

        SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

        SDL_Rect message_rect;
        message_rect.x = _pos.x;
        message_rect.y = _pos.y;
        message_rect.w = height;
        message_rect.h = width;

        SDL_RenderCopy(renderer, message, nullptr, &message_rect);

        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(message);

    }
}
