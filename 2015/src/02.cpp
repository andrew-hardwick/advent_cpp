#include "02.h"

#include <algorithm>
#include <functional>
#include <string>
#include <utility>
#include <vector>

#include "stringUtils.h"
#include "fileOps.h"


namespace advent { namespace y2015 { namespace d02
{
	int calculatePartOne(
			const std::vector<int>& dimensions)
	{
			auto smallSide = 3 * dimensions.at(0) * dimensions.at(1);
			auto sideTwo = 2 * dimensions.at(0) * dimensions.at(2);
			auto sideThree = 2 * dimensions.at(1) * dimensions.at(2);

			return smallSide + sideTwo + sideThree;
	}

	int calculatePartTwo(
			const std::vector<int>& dimensions)
	{
			auto ribbon = 2 * (dimensions.at(0) + dimensions.at(1));
			auto bow = dimensions.at(0) * dimensions.at(1) * dimensions.at(2);

			return ribbon + bow;
	}

	std::string execute(
			const std::string& inFilename,
			std::function<int(const std::vector<int>&)> calculator)
	{
		auto source = utility::fileOps::readFileToLines(inFilename);

		int result = 0;

		for (const auto& line : source)
		{
			auto split = utility::string::split(line, "x");

			auto dimensions = utility::string::convertToIntArray(split);

			std::sort(dimensions.begin(), dimensions.end());

			result += calculator(dimensions);
		}

		return std::to_string(result);
	}

	std::string partOne(
			const std::string& inFilename)
	{
		return execute(inFilename, calculatePartOne);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		return execute(inFilename, calculatePartTwo);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return std::make_pair(partOne, partTwo);
	}
} } }

