#pragma once

#include <vector>
#include "Drawable.h"

namespace super_mouse
{
    class Figure;

    class Brick final : public Drawable
    {
    public:
        Brick();

        // Initialize the location in relative values of the playing field, e.g (5,6) -> (5*unit, 6*unit)
        void setWorldLocation(const glm::ivec2& location);
        glm::ivec2 getWorldLocation() const { return _worldLocation; }

        void setRelLocation(const glm::ivec2& location);
        glm::ivec2 getRelLocation() const { return _relLocation; }

        void render(SDL_Renderer* renderer) override;

    protected:
        glm::ivec2 _worldLocation{};
        glm::ivec2 _relLocation{};

    private:
        std::vector<SDL_Rect> _rects;
        void setRectsLoc(const glm::ivec2& location);
    };
}  // namespace super_mouse


