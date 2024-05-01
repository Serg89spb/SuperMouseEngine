#include "Figure.h"

namespace super_mouse
{

    namespace
    {
        // TODO remove from this
        std::vector<std::vector<glm::vec2>> all_figures_pos = {
            {{0, 0}, {1, 0}, {0, 1}, {1, 1}},  // Square
            {{0, 0}, {1, 0}, {2, 0}, {3, 0}},  // I
            {{0, 0}, {1, 0}, {2, 0}, {0, 1}},  // L
            {{0, 0}, {1, 0}, {2, 0}, {1, 1}},  // T
            {{0, 0}, {1, 0}, {1, 1}, {2, 1}},  // Z
        };

        std::map<unsigned int, glm::vec2> pivots = {
            {0, {0.5f, 0.5f}},  // Square
            {1, {1.0f, 0.0f}},  // I
            {2, {1.0f, 0.0f}},  // L
            {3, {1.0f, 1.0f}},  // T
            {4, {1.0f, 0.0f}},  // Z
        };

    }  // namespace

    void Figure::setLocation(const glm::ivec2& loc)
    {
        for (auto& brick : _bricks)
        {
            brick.setWorldLocation(loc + brick.getRelLocation());
        }
        _location = loc;
    }

    void Figure::render(SDL_Renderer* renderer)
    {
        for (auto& brick : _bricks)
        {
            brick.render(renderer);
        }
    }

    bool Figure::updateTransformCheckedY(const Control& control, const std::vector<glm::ivec2>& bottomBricksPos)
    {
        auto pos = _location;
        pos.x += control.offsetX;
        if (control.accelerate) pos.y++;
        if (control.needRotate) rotate(bottomBricksPos);

        if (checkCollisionX(pos, bottomBricksPos))
        {
            pos.x = _location.x;
        }

        bool collided = false;
        if (checkCollisionY(pos, bottomBricksPos))
        {
            collided = true;
        }
        else
        {
            setLocation(pos);
        }
        return collided;
    }

    void Figure::rotate(const std::vector<glm::ivec2>& bottomBricksPos)
    {
        auto rotateBricks([&]()
            {
                for (auto& brick : _bricks)
                {
                    const glm::vec2 fltPoint = { (float)brick.getRelLocation().x, (float)brick.getRelLocation().y };
                    const auto relPoint = fltPoint - _pivot;

                    const float newX = -relPoint.y;
                    const float newY = relPoint.x;

                    const auto fltNewPos = _pivot + glm::vec2{ newX, newY };
                    glm::ivec2 newPos = { (int)fltNewPos.x, (int)fltNewPos.y };

                    brick.setRelLocation(newPos);
                }
                if (++_rotation == 4) { _rotation = 0; }
            });

        const auto previousRot = _rotation;
        rotateBricks();
        if (checkCollisionX(_location, bottomBricksPos))
        {
            while (_rotation != previousRot)
            {
                rotateBricks();
            }
        }
    }

    bool Figure::checkCollisionX(const glm::ivec2& nextPos, const std::vector<glm::ivec2>& bottomBricks) const
    {
        for (const auto& brick : _bricks)
        {
            const auto nextElemPos = brick.getRelLocation() + nextPos;
            for (auto& btBrick : bottomBricks)
            {
                if (nextElemPos == btBrick) return true;
            }
            if (nextElemPos.x < game_field::min_x || nextElemPos.x > game_field::max_x) return true;
        }
        return false;
    }

    bool Figure::checkCollisionY(const glm::ivec2& nextPos, const std::vector<glm::ivec2>& bottomBricks) const
    {
        for (const auto& brick : _bricks)
        {
            const auto nextElemPos = brick.getRelLocation() + nextPos;
            for (auto& btBrick : bottomBricks)
            {
                if (nextElemPos == btBrick) return true;
            }
            if (nextElemPos.y >= game_field::max_y)
            {
                return true;
            }
        }
        return false;
    }

    void Figure::generate()
    {
        _location = {};
        const int maxIndex = static_cast<int>(all_figures_pos.size()) - 1;
        const unsigned int index = getRandomInt(0, maxIndex);

        _pivot = pivots[index];
        const auto locs = all_figures_pos[index];
        _bricks.clear();
        _bricks.resize(locs.size());
        for (int i = 0; i < (int)_bricks.size(); ++i)
        {
            _bricks[i].setRelLocation(locs[i]);
        }

        randomRotate();
        setLocation({ getRandomInt(1, 8), -1 });

        //TODO use another method. Calculate form frame center
        while (checkCollisionX(_location, {}))
        {
            setLocation({ getRandomInt(1, 8), -1 });
        }
    }

    void Figure::randomRotate()
    {
        for (int i = 0; i < getRandomInt(1, 3); ++i)
            rotate({});
    }
}  // namespace super_mouse
