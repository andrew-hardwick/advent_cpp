#ifndef ADVENT_EVALUATOR_H
#define ADVENT_EVALUATOR_H

#include <string>

#include "adventTypedef.h"


namespace advent {
	void evaluate(
			const std::string& year,
			const std::string& day,
			const std::string& inFilename,
			bool verbose);

	std::pair<adventFunctor, adventFunctor> getDay(
			const std::string& year,
			const std::string& day);

	std::pair<std::string, std::size_t> executePart(
			const adventFunctor& functor,
			const std::string& inFilename);
}

#endif
