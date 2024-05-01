#pragma once
#include "Drawable/Brick.h"

namespace super_mouse
{

    class Figure : public Drawable
    {
    public:
        void generate();
        void setLocation(const glm::ivec2& loc);
        void render(SDL_Renderer* renderer) override;

        //return true if collision y is checked
        bool updateTransformCheckedY(const Control& control, const std::vector<glm::ivec2>& bottomBricksPos);

        // void create() const;

        std::vector<Brick>& getBricks() { return _bricks; }
        glm::ivec2 getLocation() const { return _location; }

        void rotate(const std::vector<glm::ivec2>& bottomBricksPos);
        bool checkCollisionX(const glm::ivec2& nextPos, const std::vector<glm::ivec2>& bottomBricks) const;
        bool checkCollisionY(const glm::ivec2& nextPos, const std::vector<glm::ivec2>& bottomBricks) const;

    protected:
        glm::ivec2 _location{};
        unsigned int _rotation = 0;


    private:
        std::vector<Brick> _bricks;
        glm::vec2 _pivot{};


        void randomRotate();
    };

}  // namespace super_mouse

