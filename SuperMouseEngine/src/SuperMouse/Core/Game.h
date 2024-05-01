#pragma once

#include <vector>
#include <memory>

#include "SME_Core.h"
#include "Input.h"
#include "Drawable/Figure.h"

namespace super_mouse
{
    class AreaElement;

    class Game
    {
    public:
        Game();
        ~Game();
        bool initSdl();
        void run();
        void update();
        void updateInput();

        SDL_Window* getWindow() const { return _window; }
        SDL_Renderer* getRenderer() const { return _renderer; }

    private:
        bool _running = true;
        std::unique_ptr<AreaElement> m_frame;

        uint32_t _lastFrameTime = 0;
        uint32_t _invertGameSpeed = 25;
        uint32_t _frameCounter = 0;

        glm::ivec2 _allFieldSize = { 17, 22 };
        glm::ivec2 _winAbsoluteSize = _allFieldSize * unit;
        glm::ivec2 _gameFieldSize = { game_field::max_x, game_field::max_y };

        //TODO maybe make unique
        SDL_Window* _window = nullptr;
        SDL_Renderer* _renderer = nullptr;
        SDL_Event _inputEvent{};
        Input _input{};
        Control _control;

        Figure _figure{};

        std::vector<glm::ivec2> _bottomBricksPos;
        std::vector<int> _rmvY{};
        int _rmvX = game_field::max_x;

        void render();
        void checkLineFilled();
        void removeLines();
        void shiftAfterRemove(const int rmvY);

        void limitFps(uint32_t fpsLimit);
    };
}  // namespace super_mouse


