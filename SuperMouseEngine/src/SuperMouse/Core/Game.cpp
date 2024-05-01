#include "Game.h"
#include "Drawable/AreaElement.h"
#include "Drawable/Brick.h"
#include "Drawable/Figure.h"

namespace super_mouse
{
    namespace running
    {
        constexpr int input_move_speed = 2;
        constexpr int fps_limit = 60;
    }  // namespace running

    Game::Game()
    {
        m_frame = std::make_unique<AreaElement>();
    }

    Game::~Game() {}

    bool Game::initSdl()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            TETRIS_ERROR("SDL Init Error {0}", SDL_GetError());
            return false;
        }
        constexpr uint32_t windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

        _window = SDL_CreateWindow(
            "SDL Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _winAbsoluteSize.x, _winAbsoluteSize.y, windowFlags);

        if (!_window)
        {
            TETRIS_ERROR("SDL window not create! SDL Error: {0}", SDL_GetError());
            return false;
        }
        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

        if (!_renderer)
        {
            TETRIS_ERROR("SDL render not create! SDL Error: {0}", SDL_GetError());
            return false;
        }

        _lastFrameTime = SDL_GetTicks();
        _figure.generate();

        return true;
    }

    void Game::run()
    {
        while (_running)
        {
            CHECK(_renderer, "Renderer in NULL")

                updateInput();
            update();

            const auto bg = Color::background;
            SDL_SetRenderDrawColor(_renderer, bg.r, bg.g, bg.b, bg.a);
            SDL_RenderClear(_renderer);

            render();

            SDL_RenderPresent(_renderer);

            limitFps(running::fps_limit);
        }
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
        if (_input.exit) _running = false;

        _control.reset();
        _control.offsetX += _input.isKeyPressed(SDLK_RIGHT);
        _control.offsetX -= _input.isKeyPressed(SDLK_LEFT);

        _control.needRotate = _input.isKeyPressed(SDLK_UP);

        if (_frameCounter % running::input_move_speed == 0)
        {
            _control.offsetX += _input.isHandleHold(SDLK_RIGHT);
            _control.offsetX -= _input.isHandleHold(SDLK_LEFT);
        }

        const auto tempGameSpeed = _input.isKeyDown(SDLK_DOWN) ? running::input_move_speed : _invertGameSpeed;
        _control.accelerate = _frameCounter % tempGameSpeed == 0;
    }

    void Game::render()
    {
        m_frame->render(_renderer);
        _figure.render(_renderer);

        for (const auto& brickPos : _bottomBricksPos)
        {
            auto brick = Brick();
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

    void Game::limitFps(const uint32_t fpsLimit)
    {
        const uint32_t delta = SDL_GetTicks() - _lastFrameTime;
        if (delta < 1000 / fpsLimit)
        {
            SDL_Delay(1000 / fpsLimit - delta);
        }
        _lastFrameTime = SDL_GetTicks();
    }
}  // namespace super_mouse
