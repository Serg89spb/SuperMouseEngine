
#include <iostream>

#include "Game.h"
#include "SuperMouseEngine.h"

int main(int argc, char* args[])
{
    super_mouse::Log::init();
    const auto engineInit = new super_mouse::EngineInit();

    if (engineInit->initSdl())
    {
        if (auto sandboxGame = engineInit->createGame<sandbox::Game>())
        {
            sandboxGame->Init(engineInit->getRenderer(), engineInit);
            TETRIS_INFO("sandboxGame Init");
            engineInit->run();
        }
    }
    return 0;
}
