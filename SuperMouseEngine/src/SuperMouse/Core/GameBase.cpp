#include "GameBase.h"

namespace super_mouse
{
    void GameBase::Init(SDL_Renderer* renderer, EngineInit* engineInit)
    {
        CHECK(renderer, "Renderer in NULL");
        CHECK(engineInit, "EngineInit in NULL");
        _renderer = renderer;
        _engineInit = engineInit;
    }
}
