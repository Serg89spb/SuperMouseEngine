#pragma once

#include <vector>
#include "Drawable.h"

namespace super_mouse
{

    class Brick : public Drawable
    {
    public:
        Brick() = default;

        // Initialize the location in relative values of the playing field, e.g (5,6) -> (5*unit, 6*unit)
        Brick(glm::ivec2 location);
        void render(SDL_Renderer* renderer) override;
        void draw() override;

        glm::ivec2 get_location() const { return _location; }

    protected:
        glm::ivec2 _location{};

    private:
        std::vector<SDL_Rect> _rects;
    };

}  // namespace super_mouse


