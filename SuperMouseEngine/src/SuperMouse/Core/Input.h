#pragma once

#include "SME_Core.h"

namespace super_mouse
{

    class Input
    {
    public:
        ~Input();

        void update(SDL_Event event);

        bool isKeyDown(unsigned int keyId);
        bool isKeyPressed(unsigned int keyId);
        bool isHandleHold(unsigned int keyId);
        bool shouldQuit() const { return _shouldQuit; }

    private:
        void dispose();
        void pressKey(unsigned int keyId);
        void releaseKey(unsigned int keyId);

        bool wasKeyDown(unsigned int keyId);

        bool _shouldQuit = false;
        bool _isHolding = false;
        unsigned int _holdKeyId{};
        double _startHoldTime{};

        std::unordered_map<unsigned int, bool> _keyMap;
        std::unordered_map<unsigned int, bool> _previousKeyMap;
    };

}  // namespace super_mouse


