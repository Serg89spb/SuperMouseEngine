#include "Game.h"
#include "Utils/Log.h"

int main(int argc, char** argv)
{
    super_mouse::Log::init();
    const auto game = std::make_unique<super_mouse::Game>();

    if (game->initSdl())
    {
        game->run();
    }
    return 0;
}