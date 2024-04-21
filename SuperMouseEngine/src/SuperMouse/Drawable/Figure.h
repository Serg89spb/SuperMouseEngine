#pragma once
#include "Drawable/Brick.h"

namespace super_mouse
{

    class Figure : public Brick
    {
    public:
        Figure() = default;
        Figure(const unsigned int index, const glm::ivec2& pos);
        Figure(bool initRandom);

        void create() const;
        void setLocation(const glm::ivec2& loc) { _location = loc; }

        std::vector<glm::ivec2> getElemsPos() const { return _elemsPos; }

        void rotate();
        bool checkCollisionX(const glm::ivec2& nextPos, const std::vector<glm::ivec2>& bottomBricks) const;
        bool checkCollisionY(const glm::ivec2& nextPos, const std::vector<glm::ivec2>& bottomBricks) const;

    private:
        unsigned int _index{};
        std::vector<glm::ivec2> _elemsPos;
        glm::vec2 _pivot{};

        void initElemsPos();
        void randomRotate();
    };

}  // namespace super_mouse

