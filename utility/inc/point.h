#ifndef ADVENT_UTILITY_POINT_H
#define ADVENT_UTILITY_POINT_H

#include <ostream>


namespace advent { namespace utility
{
	struct Point
	{
		int x;
		int y;
	};

	bool operator==(
			const Point& a,
			const Point& b);

	bool operator!=(
			const Point& a,
			const Point& b);

	std::ostream& operator<<(
			std::ostream& os,
			const Point& p);

	Point operator+(
			const Point& a,
			const Point& b);

	Point operator+=(
			Point& self,
			const Point& other);
} }

#endif
