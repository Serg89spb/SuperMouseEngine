#include "Game.h"

namespace sandbox
{

    namespace running
    {
        constexpr int input_move_speed = 2;
    }  // namespace running

    using namespace super_mouse;

    void Game::Init(SDL_Renderer* renderer, EngineInit* engineInit)
    {
        GameBase::Init(renderer, engineInit);
        _figure.generate();
    }

    void Game::run()
    {
        updateInput();
        update();

        render();
    }

    void Game::update()
    {
        if (_figure.updateTransformCheckedY(_control, _bottomBricksPos))
        {
            for (const auto& brick : _figure.getBricks())
            {
                addUnique(brick.getWorldLocation(), _bottomBricksPos);
            }
            _figure.generate();

            checkLineFilled();
        }
        if (!_rmvY.empty()) removeLines();
        if (_frameCounter++ == INT_MAX) _frameCounter = 0;
    }

    void Game::updateInput()
    {
        _input.update(_inputEvent);
        if (_input.shouldQuit()) _engineInit->shouldQuit();

        // control -> input_state
        _control.reset();
        _control.offsetX += _input.isKeyPressed(SDLK_RIGHT);
        _control.offsetX -= _input.isKeyPressed(SDLK_LEFT);

        _control.needRotate = _input.isKeyPressed(SDLK_UP);

        if (_frameCounter % running::input_move_speed == 0)
        {
            _control.offsetX += _input.isHandleHold(SDLK_RIGHT);
            _control.offsetX -= _input.isHandleHold(SDLK_LEFT);
        }

        //
        const auto tempGameSpeed = _input.isKeyDown(SDLK_DOWN) ? running::input_move_speed : _invertGameSpeed;
        _control.accelerate = _frameCounter % tempGameSpeed == 0;
    }

    void Game::render()
    {
        _figure.render(_renderer);

        for (const auto& brickPos : _bottomBricksPos)
        {
            auto brick = Brick();// ctor - brickPos
            brick.setWorldLocation(brickPos);
            brick.render(_renderer);
        }
    }

    // fillReadyLines
    void Game::checkLineFilled()
    {
        _rmvY.clear();
        sortVec2Y(_bottomBricksPos);

        int prevY = -1;
        int gapLength = 0;
        int currentY = 0;

        for (const auto& point : _bottomBricksPos)
        {
            currentY = point.y;
            for (const int& elem : _rmvY)
            {
                if (elem == currentY) return;
            }

            if (prevY != currentY)
            {
                if (gapLength == game_field::max_x)
                {
                    addUnique(prevY, _rmvY);
                }
                gapLength = 0;
            }
            else
            {
                gapLength++;
            }
            prevY = currentY;
        }

        if (gapLength == game_field::max_x)
        {
            addUnique(currentY, _rmvY);
        }
    }

    void Game::removeLines()
    {
        for (const int& elemY : _rmvY)
        {
            glm::ivec2 rmvPoint = { _rmvX, elemY };
            const auto it = std::remove_if(
                _bottomBricksPos.begin(), _bottomBricksPos.end(), [rmvPoint](const glm::ivec2& elem) { return elem == rmvPoint; });
            _bottomBricksPos.erase(it, _bottomBricksPos.end());
        }

        if (_rmvX > 0)
        {
            _rmvX--;
        }
        else
        {
            _rmvX = game_field::max_x;
            std::reverse(_rmvY.begin(), _rmvY.end());
            for (const int& elem : _rmvY)
            {
                shiftAfterRemove(elem);
            }
            _rmvY.clear();
        }
    }

    void Game::shiftAfterRemove(const int rmvY)
    {
        for (auto& point : _bottomBricksPos)
        {
            if (point.y <= rmvY)
            {
                point.y++;
            }
        }
    }
}
