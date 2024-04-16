#pragma once

namespace super_mouse
{

	template <typename T>
	struct Vec2
	{
		Vec2<T>();
		Vec2<T>(T x, T y);

		Vec2<T> operator+(const Vec2<T>& v) const;
		Vec2<T> operator-(const Vec2<T>& v) const;
		Vec2<T> operator*(const T& s) const;
		Vec2<T> operator/(const T& s) const;
		bool operator==(const Vec2<T>& v) const;

		T x, y;
	};

	template <typename T>
	Vec2<T>::Vec2() : x{}, y{}
	{
	}

	template <typename T>
	Vec2<T>::Vec2(T x, T y) : x(x), y(y)
	{
	}

	template <typename T>
	Vec2<T> Vec2<T>::operator+(const Vec2<T>& v) const
	{
		return { x + v.x, y + v.y };
	}

	template <typename T>
	Vec2<T> Vec2<T>::operator-(const Vec2<T>& v) const
	{
		return { x - v.x, y - v.y };
	}

	template <typename T>
	Vec2<T> Vec2<T>::operator*(const T& s) const
	{
		return { x * s, y * s };
	}

	template <typename T>
	Vec2<T> Vec2<T>::operator/(const T& s) const
	{
		const T rs = 1.f / s;
		return { x * rs, y * rs };
	};

	template <typename T>
	bool Vec2<T>::operator==(const Vec2<T>& v) const
	{
		return x == v.x && y == v.y;
	};

}  // namespace super_mouse
