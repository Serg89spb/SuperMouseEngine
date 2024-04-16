#pragma once
#include "Drawable/Brick.h"

namespace super_mouse
{

	class Figure : public Brick
	{
	public:
		Figure() = default;
		Figure(const unsigned int index, const Vec2<int>& pos);
		Figure(bool initRandom);

		void create() const;
		void setLocation(const Vec2<int>& loc) { _location = loc; }

		std::vector<Vec2<int>> getElemsPos() const { return _elemsPos; }

		void rotate();
		bool checkCollisionX(const Vec2<int>& nextPos, const std::vector<Vec2<int>>& bottomBricks) const;
		bool checkCollisionY(const Vec2<int>& nextPos, const std::vector<Vec2<int>>& bottomBricks) const;

	private:
		unsigned int _index{};
		std::vector<Vec2<int>> _elemsPos;
		Vec2<float> _pivot{};

		void initElemsPos();
		void randomRotate();
	};

}  // namespace super_mouse

