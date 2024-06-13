#pragma once
#include "EngineInit.h"
#include "SME_Core.h"

namespace super_mouse
{
    class GameBase
    {
    public:
        GameBase() {}
        virtual ~GameBase() {}
        virtual void Init(SDL_Renderer* renderer, EngineInit* engineInit);

        virtual void run() {}

    protected:
        SDL_Renderer* _renderer = nullptr;
        EngineInit* _engineInit = nullptr;
    };
}
