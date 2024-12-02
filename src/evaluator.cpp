#include "evaluator.h"

#include <chrono>
#include <iostream>
#include <stdexcept>

#include "lib2015.h"
#include "lib2024.h"


namespace advent
{
	void evaluate(
			const std::string& year,
			const std::string& day,
			const std::string& inFilename,
			bool verbose)
	{
		auto [ partOne, partTwo ] = getDay(year, day);

		if (verbose)
		{
			std::cout << "Starting part one.\n";
		}

		auto [ partOneResult, partOneTime ] = executePart(partOne, inFilename);

		if (verbose)
		{
			std::cout << "Part One: '" << partOneResult << "' in " << partOneTime << "us.\n";
			std::cout << "Starting part two.\n";
		}
		else
		{
			std::cout << "p1: '" << partOneResult << "'\n";
		}

		auto [ partTwoResult, partTwoTime ] = executePart(partTwo, inFilename);

		if (verbose)
		{
			std::cout << "Part Two: '" << partTwoResult << "' in " << partTwoTime << "us.\n";
		}
		else
		{
			std::cout << "p2: '" << partTwoResult << "'\n";
		}
	}


	std::pair<adventFunctor, adventFunctor> getDay(
			const std::string& year,
			const std::string& day)
	{
		if ("2015" == year)
			return y2015::getDay(day);
		if ("2024" == year)
			return y2024::getDay(day);

		throw std::invalid_argument("Encountered unparseable year");
	}

	std::pair<std::string, std::size_t> executePart(
			const adventFunctor& functor,
			const std::string& inFilename)
	{
		auto before = std::chrono::high_resolution_clock::now();

		auto result = functor(inFilename);

		auto after = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(after - before).count();

		return std::make_pair(result, duration);
	}
}
