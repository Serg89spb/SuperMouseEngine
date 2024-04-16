#include "Input.h"

namespace super_mouse
{
	namespace
	{
		constexpr int hold_delay = 250;  // ms
	}

	Input::~Input()
	{
		dispose();
	}

	void Input::dispose()
	{
		_keyMap.clear();
		_previousKeyMap.clear();
	}

	void Input::update(SDL_Event event)
	{
		for (auto& it : _keyMap)
		{
			_previousKeyMap[it.first] = it.second;
		}

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: exit = true; break;

			case SDL_KEYDOWN:
				pressKey(event.key.keysym.sym);
				_isHolding = true;
				break;

			case SDL_KEYUP:
				releaseKey(event.key.keysym.sym);
				_isHolding = false;
				break;
			default: break;
			}
		}
	}

	void Input::pressKey(const unsigned keyId)
	{
		_keyMap[keyId] = true;
	}

	void Input::releaseKey(const unsigned keyId)
	{
		_keyMap[keyId] = false;
	}

	bool Input::isKeyDown(const unsigned int keyId)
	{
		const auto it = _keyMap.find(keyId);
		return it != _keyMap.end() ? it->second : false;
	}

	bool Input::isKeyPressed(const unsigned int keyId)
	{
		if (isKeyDown(keyId) && !wasKeyDown(keyId))
		{
			_holdKeyId = keyId;
			_startHoldTime = getTimeMilliseconds();
		}
		return isKeyDown(keyId) && !wasKeyDown(keyId);
	}

	bool Input::wasKeyDown(const unsigned int keyId)
	{
		const auto it = _previousKeyMap.find(keyId);
		return it != _previousKeyMap.end() ? it->second : false;
	}

	bool Input::isHandleHold(const unsigned int keyId)
	{
		return _isHolding && isKeyDown(keyId) && keyId == _holdKeyId && getTimeMilliseconds() - _startHoldTime > hold_delay;
	}

}  // namespace super_mouse
