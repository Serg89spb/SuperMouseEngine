#pragma once
#include <SDL_render.h>
#include "Utils/Color.h"

namespace super_mouse
{

	class Drawable
	{
	public:
		virtual ~Drawable() = default;

		virtual void render(SDL_Renderer* renderer) = 0;
		virtual void draw() = 0;

	protected:
		SDL_Renderer* _renderer = nullptr;
		Color _bg = Color::background;
		Color _fl = Color::fill;
	};

}  // namespace super_mouse


