#pragma once

#include <memory>
#include "SME_Core.h"

namespace super_mouse
{
    class GameBase;
    class AreaElement;

    class EngineInit
    {
    public:
        EngineInit();
        ~EngineInit();
        bool initSdl();
        void run();

        SDL_Window* getWindow() const { return _window; }
        SDL_Renderer* getRenderer() const { return _renderer; }
        void shouldQuit() { _running = false; }

        template<typename T>
        T* createGame()
        {
            T* game = new T;
            _game = game;
            return game;
        }

    private:
        bool _running = true;
        std::unique_ptr<AreaElement> m_frame;

        uint32_t _lastFrameTime = 0;
        glm::ivec2 _allFieldSize = { 16, 22 };
        glm::ivec2 _winAbsoluteSize = _allFieldSize * unit;
        glm::ivec2 _gameFieldSize = { game_field::max_x, game_field::max_y };

        //TODO maybe make unique
        SDL_Window* _window = nullptr;
        SDL_Renderer* _renderer = nullptr;
        Control _control;

        GameBase* _game = nullptr;

        void limitFps(uint32_t fpsLimit);
    };
}  // namespace super_mouse


