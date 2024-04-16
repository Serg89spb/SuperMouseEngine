#include "Brick.h"
#include "SME_Core.h"

namespace super_mouse
{
	namespace
	{
		Vec2<int> size = { unit, unit };
		constexpr int offset1 = 1;
		constexpr int offset2 = 3;
		constexpr int offset3 = 6;
	}  // namespace

	Brick::Brick(const Vec2<int> location) : _location(location)
	{
		_location = _location * unit;

		_rects.push_back({ _location.x, _location.y, size.x, size.y });
		_rects.push_back({ _location.x + offset1, _location.y + offset1, size.x - offset1 * 2, size.y - offset1 * 2 });
		_rects.push_back({ _location.x + offset2, _location.y + offset2, size.x - offset2 * 2, size.y - offset2 * 2 });
		_rects.push_back({ _location.x + offset3, _location.y + offset3, size.x - offset3 * 2, size.y - offset3 * 2 });
	}

	void Brick::draw()
	{
		if (!_renderer)
		{
			throw std::runtime_error("renderer must be initialized");
		}

		bool renderRect = true;
		if (_location.x < game_field::min_x * unit || _location.x > game_field::max_x * unit ||  //
			_location.y < game_field::min_y * unit || _location.y > game_field::max_y * unit)    //
		{
			renderRect = false;
		}

		if (renderRect)
		{
			bool isBgColor = true;
			for (const auto& rect : _rects)
			{
				const auto clr = isBgColor ? _bg : _fl;
				SDL_SetRenderDrawColor(_renderer, clr.r, clr.g, clr.b, clr.a);
				SDL_RenderFillRect(_renderer, &rect);
				isBgColor = !isBgColor;
			}
		}
	}

	void Brick::render(SDL_Renderer* renderer)
	{
		if (!renderer)
		{
			throw std::runtime_error("renderer must be initialized");
		}
		_renderer = renderer;
	}
}  // namespace super_mouse
