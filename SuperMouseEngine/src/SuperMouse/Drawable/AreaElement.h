#pragma once
#include "Drawable.h"

namespace super_mouse
{

	class AreaElement final : public Drawable
	{
	public:
		AreaElement() = default;

		void render(SDL_Renderer* renderer) override;
		void draw() override {}
		void createFrame() const;
	};

}  // namespace super_mouse


