#pragma once

#include <vector>

#include "Drawable.h"
#include "Utils/Vec2.h"

namespace super_mouse
{

	class Brick : public Drawable
	{
	public:
		Brick() = default;

		// Initialize the location in relative values of the playing field, e.g (5,6) -> (5*unit, 6*unit)
		Brick(Vec2<int> location);
		void render(SDL_Renderer* renderer) override;
		void draw() override;

		Vec2<int> get_location() const { return _location; }

	protected:
		Vec2<int> _location{};

	private:
		std::vector<SDL_Rect> _rects;
	};

}  // namespace super_mouse


