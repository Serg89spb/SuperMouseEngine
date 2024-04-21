#include "Figure.h"

namespace super_mouse
{

    namespace
    {
        // TODO remove from this
        std::vector<std::vector<glm::ivec2>> all_figures_pos = {
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

    Figure::Figure(const unsigned int index, const glm::ivec2& pos) : _index(index)
    {
        _location = pos;
        initElemsPos();
    }

    Figure::Figure(const bool initRandom)
    {
        if (initRandom)
        {
            const int maxIndex = static_cast<int>(all_figures_pos.size()) - 1;
            _index = getRandomInt(0, maxIndex);
            initElemsPos();
            randomRotate();
            _location = { getRandomInt(1, 8), 2 };
            while (checkCollisionX(_location, {}))
            {
                _location = { getRandomInt(1, 8), 2 };
            }
        }
    }

    void Figure::create() const
    {
        if (!_renderer)
        {
            throw std::runtime_error("renderer must be initialized");
        }

        for (const auto& oneBrickPos : _elemsPos)
        {
            Brick brick(_location + oneBrickPos);
            brick.render(_renderer);
            brick.draw();
        }
    }

    void Figure::rotate()
    {
        const auto currentsPos = _elemsPos;
        _elemsPos.clear();
        for (const glm::ivec2& point : currentsPos)
        {
            const glm::vec2 fltPoint = { (float)point.x, (float)point.y };
            const auto relPoint = fltPoint - _pivot;

            const float newX = -relPoint.y;
            const float newY = relPoint.x;

            const auto fltNewPos = _pivot + glm::vec2{ newX, newY };
            glm::ivec2 newPos = { (int)fltNewPos.x, (int)fltNewPos.y };

            _elemsPos.push_back(newPos);
        }
    }

    bool Figure::checkCollisionX(const glm::ivec2& nextPos, const std::vector<glm::ivec2>& bottomBricks) const
    {
        for (const auto& elem : _elemsPos)
        {
            const auto nextElemPos = elem + nextPos;
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
        for (const auto& elem : _elemsPos)
        {
            const auto nextElemPos = elem + nextPos;
            for (auto& btBrick : bottomBricks)
            {
                if (nextElemPos == btBrick) return true;
            }
            if (nextElemPos.y >= game_field::max_y) return true;
        }
        return false;
    }

    void Figure::initElemsPos()
    {
        _elemsPos.clear();
        _elemsPos = all_figures_pos[_index];
        _pivot = pivots[_index];
    }

    void Figure::randomRotate()
    {
        for (int i = 0; i < getRandomInt(1, 3); ++i)
            rotate();
    }
}  // namespace super_mouse
