#pragma once

#include <vector>

#include "SME_Core.h"
#include "Input.h"
#include "Drawable/Figure.h"

namespace super_mouse
{

	class Game
	{
	public:
		Game() = default;

		bool initSdl();
		void update();

		SDL_Window* getWindow() const { return _window; }
		SDL_Renderer* getRenderer() const { return _renderer; }

	private:
		bool _running = true;

		Uint32 _lastFrameTime = 0;
		Uint32 _invertGameSpeed = 25;
		Uint32 _gameCounter = 0;

		Vec2<int> _allFieldSize = { 17, 25 };
		Vec2<int> _winAbsoluteSize = _allFieldSize * unit;
		Vec2<int> _gameFieldSize = { game_field::max_x, game_field::max_y };

		SDL_Window* _window = nullptr;
		SDL_Renderer* _renderer = nullptr;
		SDL_Event _inputEvent{};
		Input _input{};

		Figure _currentFig{};

		std::vector<Vec2<int>> _bottomBricksPos;
		std::vector<int> _rmvY{};
		int _rmvX = game_field::max_x;

		void gameRender();
		void drawFigure();
		void drawBottomBricks() const;
		void checkLineFilled();
		void startRemoveIfFilled();
		void shiftAfterRemove(const int rmvY);

		void limitFps(Uint32 fpsLimit);
	};
}  // namespace super_mouse


