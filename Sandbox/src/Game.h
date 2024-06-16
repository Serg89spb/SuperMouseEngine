#pragma once
#include "Core/GameBase.h"
#include "Drawable/Figure.h"
#include "SuperMouseEngine.h"
#include "Core/Input.h"

namespace sandbox
{
    class AreaElement;

    class Game : public super_mouse::GameBase
    {
    public:
        Game() {}
        ~Game() {}
        virtual void Init(SDL_Renderer* renderer, super_mouse::EngineInit* engineInit) override;
        virtual void run() override;
    private:
        bool _gameOver = false;

        uint32_t _invertGameSpeed = 21;
        uint32_t _frameCounter = 0;

        SDL_Event _inputEvent{};
        super_mouse::Input _input{};
        super_mouse::Control _control;

        super_mouse::Figure _figure{};

        std::vector<glm::ivec2> _bottomBricksPos;
        std::vector<int> _rmvY{};
        int _rmvX = super_mouse::game_field::max_x;

        void update();
        void updateInput();

        void render();
        void checkLineFilled();
        void removeLines();
        void shiftAfterRemove(const int rmvY);
        void updateScore(int scoreFactor) const;
    };
}
