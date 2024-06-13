#include "EngineInit.h"

#include "GameBase.h"
#include "Drawable/AreaElement.h"
#include "Drawable/Brick.h"

// EngineDLL <- EngineLib

// GameLib <- EngineLib
// mainEXE <- GameLib
// gameTests <- GameLib

namespace super_mouse
{
    namespace running
    {
        constexpr int fps_limit = 60;
    }  // namespace running

    EngineInit::EngineInit()
    {
        m_frame = std::make_unique<AreaElement>();
    }

    EngineInit::~EngineInit() {}

    bool EngineInit::initSdl()
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

        return true;
    }

    void EngineInit::run()
    {
        while (_running)
        {
            CHECK(_renderer, "Renderer in NULL");
            CHECK(_game, "Game in NULL");

            const auto bg = Color::background;
            SDL_SetRenderDrawColor(_renderer, bg.r, bg.g, bg.b, bg.a);
            SDL_RenderClear(_renderer);

            m_frame->render(_renderer);
            _game->run();

            SDL_RenderPresent(_renderer);

            limitFps(running::fps_limit);
        }
    }

    void EngineInit::limitFps(const uint32_t fpsLimit)
    {
        const uint32_t delta = SDL_GetTicks() - _lastFrameTime;
        if (delta < 1000 / fpsLimit)
        {
            SDL_Delay(1000 / fpsLimit - delta);
        }
        _lastFrameTime = SDL_GetTicks();
    }
}  // namespace super_mouse
