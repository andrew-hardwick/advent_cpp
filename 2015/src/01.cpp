#include "01.h"

#include <cmath>
#include <string>
#include <utility>

#include "fileOps.h"


namespace advent { namespace y2015 { namespace d01
{
	void performStep(
			int& floor,
			char step)
	{
		if (step == '(')
		{
			floor++;
		}
		else if (step == ')')
		{
			floor--;
		}
	}

	std::string partOne(
			const std::string& inFilename)
	{
		int floor = 0;

		auto source = utility::fileOps::readFileToChars(inFilename);

		for (const auto& inst : source)
		{
			performStep(floor, inst);
		}

		return std::to_string(floor);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		int floor = 0;
		std::size_t steps = 0;

		auto source = utility::fileOps::readFileToChars(inFilename);

		for (const auto& inst : source)
		{
			steps++;

			performStep(floor, inst);

			if (floor == -1)
			{
				return std::to_string(steps);
			}
		}

		return "Santa never entered the basement.";
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return std::make_pair(partOne, partTwo);
	}
} } }

