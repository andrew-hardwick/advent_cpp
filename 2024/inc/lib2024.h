#ifndef ADVENT_2024_H
#define ADVENT_2024_H

#include <string>

#include "adventTypedef.h"


namespace advent { namespace y2024
{
	std::pair<adventFunctor, adventFunctor> getDay(
			const std::string& day);
} }

#endif
