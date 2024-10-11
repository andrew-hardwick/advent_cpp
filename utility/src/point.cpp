#include "point.h"


namespace advent { namespace utility
{
	bool operator==(
			const Point& a,
			const Point& b)
	{
		if (a.x != b.x)
			return false;
		if (a.y != b.y)
			return false;

		return true;
	}

	bool operator!=(
			const Point& a,
			const Point& b)
	{
		return !(a == b);
	}

	std::ostream& operator<<(
			std::ostream& os,
			const Point& p)
	{
		os << "{ " << p.x << ", " << p.y << " }";

		return os;
	}

	Point operator+(
			const Point& a,
			const Point& b)
	{
		return { a.x + b.x, a.y + b.y };
	}

	Point operator+=(
			Point& self,
			const Point& other)
	{
		return self + other;
	}
} }

