#include "Game.h"

#include "Drawable/RightBar.h"

namespace sandbox
{

    namespace running
    {
        constexpr int input_move_speed = 1;
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

            for (auto& btBrick : _bottomBricksPos)
            {
                if (btBrick.y <= game_field::min_y)
                {
                    _gameOver = true;
                    if (const auto bar = _engineInit->rightBar())
                    {
                        bar->setTextVisibility(GameOver, true);
                    }
                    return;
                }
            }

        }
        if (!_rmvY.empty()) removeLines();
        if (_frameCounter++ == INT_MAX) _frameCounter = 0;
    }

    void Game::updateInput()
    {
        _input.update(_inputEvent);
        if (_input.shouldQuit()) _engineInit->shouldQuit();

        if (_gameOver)
        {
            _control.reset();
            return;
        }

        if (_input.isKeyPressed(SDLK_ESCAPE))
        {
            _input.setIsPause(!_input.isPause());
            _engineInit->rightBar()->setTextBlinking(Pause, _input.isPause());
            _control.reset();
            return;
        }
        if (_input.isPause()) return;

        if (_input.isKeyPressed(SDLK_e))
        {
            if (_invertGameSpeed >= 4)
            {
                _invertGameSpeed -= 2;
                TETRIS_INFO("Game Speed: {0}", _invertGameSpeed);
                if (const auto bar = _engineInit->rightBar())
                {
                    bar->setNumberSpeed(bar->getSpeed() + 1);
                }
            }
        }

        _control.reset();
        _control.offsetX += _input.isKeyPressed(SDLK_RIGHT);
        _control.offsetX -= _input.isKeyPressed(SDLK_LEFT);

        _control.needRotate = _input.isKeyPressed(SDLK_UP);

        //if (_frameCounter % running::input_move_speed == 0)
        //{
        _control.offsetX += _input.isHandleHold(SDLK_RIGHT);
        _control.offsetX -= _input.isHandleHold(SDLK_LEFT);
        //}

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

            int scoreFactor = 0;
            for (const int& elem : _rmvY)
            {
                shiftAfterRemove(elem);
                scoreFactor++;
            }
            _rmvY.clear();
            updateScore(scoreFactor);
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

    void Game::updateScore(int scoreFactor) const
    {
        for (int i = 1; i <= scoreFactor; ++i)
        {
            if (const auto bar = _engineInit->rightBar())
            {
                bar->setNumberScore(bar->getScore() + 100 * i);
            }

        }
    }
}
