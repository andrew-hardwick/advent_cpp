#ifndef ADVENT_COMBINATORICS_H
#define ADVENT_COMBINATORICS_H

#include <vector>


namespace advent { namespace utility { namespace combinatorics
{
	std::vector<std::vector<std::size_t>> combinations(
			std::size_t length);
	
	std::vector<std::vector<std::size_t>> permutations(
			std::size_t length);
} } }

#endif

