#include "Game.h"
#include "Drawable/AreaElement.h"
#include "Drawable/Brick.h"
#include "Drawable/Figure.h"

namespace super_mouse
{
	namespace running
	{
		constexpr int input_move_speed = 2;
		constexpr int fps_limit = 60;
	}  // namespace running

	bool Game::initSdl()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			TETRIS_ERROR("SDL Init Error {0}", SDL_GetError());
			return false;
		}
		constexpr Uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

		_window = SDL_CreateWindow(
			"SDL Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _winAbsoluteSize.x, _winAbsoluteSize.y, windowFlags);
		if (!_window)
		{
			TETRIS_ERROR("SDL window not create! SDL Error: {0}", SDL_GetError());
			return false;
		}
		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

		if (!_renderer)
		{
			TETRIS_ERROR("SDL render not create! SDL Error: {0}", SDL_GetError());
			return false;
		}

		_lastFrameTime = SDL_GetTicks();
		_currentFig = Figure(true);

		return true;
	}

	void Game::update()
	{
		while (_running)
		{
			if (!_renderer)
			{
				throw std::runtime_error("renderer must be initialized");
			}

			const auto bg = Color::background;
			SDL_SetRenderDrawColor(_renderer, bg.r, bg.g, bg.b, bg.a);
			SDL_RenderClear(_renderer);

			gameRender();

			SDL_RenderPresent(_renderer);

			limitFps(running::fps_limit);
		}
	}

	void Game::gameRender()
	{
		AreaElement frame;
		frame.render(_renderer);
		frame.createFrame();

		drawFigure();
	}

	void Game::drawFigure()
	{
		_input.update(_inputEvent);
		if (_input.exit) _running = false;

		auto figPos = _currentFig.get_location();

		figPos.x -= _input.isKeyPressed(SDLK_LEFT);
		figPos.x += _input.isKeyPressed(SDLK_RIGHT);
		if (_input.isKeyPressed(SDLK_UP)) _currentFig.rotate();

		if (_gameCounter % running::input_move_speed == 0)
		{
			figPos.x -= _input.isHandleHold(SDLK_LEFT);
			figPos.x += _input.isHandleHold(SDLK_RIGHT);
		}

		const auto tempGameSpeed = _input.isKeyDown(SDLK_DOWN) ? running::input_move_speed : _invertGameSpeed;
		if (_gameCounter % tempGameSpeed == 0)
		{
			figPos.y++;
		}
		if (_gameCounter == INT_MAX) _gameCounter = 0;
		_gameCounter++;

		if (_currentFig.checkCollisionX(figPos, _bottomBricksPos))
		{
			figPos.x = _currentFig.get_location().x;
		}

		if (_currentFig.checkCollisionY(figPos, _bottomBricksPos))
		{
			for (const auto& figBrickPos : _currentFig.getElemsPos())
			{
				addUnique(figBrickPos + _currentFig.get_location(), _bottomBricksPos);
			}
			checkLineFilled();

			_currentFig = Figure(true);
			figPos = _currentFig.get_location();
		}

		startRemoveIfFilled();

		drawBottomBricks();

		_currentFig.setLocation(figPos);
		_currentFig.render(_renderer);
		_currentFig.create();
	}

	void Game::checkLineFilled()
	{
		_rmvY.clear();
		sortVec2Y(_bottomBricksPos);

		int prevY = -1;
		int gapLength = 0;
		int currentY = 0;

		for (const auto& point : _bottomBricksPos)
		{
			currentY = point.y;
			for (const int& elem : _rmvY)
			{
				if (elem == currentY) return;
			}

			if (prevY != currentY)
			{
				if (gapLength == game_field::max_x)
				{
					addUnique(prevY, _rmvY);
				}
				gapLength = 0;
			}
			else
			{
				gapLength++;
			}
			prevY = currentY;
		}

		if (gapLength == game_field::max_x)
		{
			addUnique(currentY, _rmvY);
		}
	}

	void Game::startRemoveIfFilled()
	{
		if (_rmvY.empty()) return;
		for (const int& elemY : _rmvY)
		{
			Vec2<int> rmvPoint = { _rmvX, elemY };
			const auto it = std::remove_if(
				_bottomBricksPos.begin(), _bottomBricksPos.end(), [rmvPoint](const Vec2<int>& elem) { return elem == rmvPoint; });
			_bottomBricksPos.erase(it, _bottomBricksPos.end());
		}

		if (_rmvX > 0)
		{
			_rmvX--;
		}
		else
		{
			_rmvX = game_field::max_x;
			std::reverse(_rmvY.begin(), _rmvY.end());
			for (const int& elem : _rmvY)
			{
				shiftAfterRemove(elem);
			}
			_rmvY.clear();
		}
	}

	void Game::shiftAfterRemove(const int rmvY)
	{
		for (auto& point : _bottomBricksPos)
		{
			if (point.y <= rmvY)
			{
				point.y++;
			}
		}
	}

	void Game::drawBottomBricks() const
	{
		for (const auto& brickPos : _bottomBricksPos)
		{
			auto brick = Brick(brickPos);
			brick.render(_renderer);
			brick.draw();
		}
	}

	void Game::limitFps(const Uint32 fpsLimit)
	{
		const Uint32 delta = SDL_GetTicks() - _lastFrameTime;
		if (delta < 1000 / fpsLimit)
		{
			SDL_Delay(1000 / fpsLimit - delta);
		}
		_lastFrameTime = SDL_GetTicks();
	}
}  // namespace super_mouse
