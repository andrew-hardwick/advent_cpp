#ifndef ADVENT_2015_H
#define ADVENT_2015_H

#include <string>

#include "adventTypedef.h"


namespace advent { namespace y2015
{
	std::pair<adventFunctor, adventFunctor> getDay(
			const std::string& day);
} }

#endif
