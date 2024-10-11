#include "03.h"

#include <algorithm>
#include <map>
#include <vector>

#include "fileOps.h"
#include "point.h"


namespace advent { namespace y2015 { namespace d03
{
	std::string walkNSantas(
			const std::string& inFilename,
			std::size_t n)
	{
		const auto source = utility::fileOps::readFileToChars(inFilename);

		std::vector<utility::Point> visited;

		std::map<char, utility::Point> stepMap {
			{'<', {-1, 0}},
			{'>', {1, 0}},
			{'v', {0, -1}},
			{'^', {0, 1}}
		};

		std::vector<utility::Point> santaPositions;

		for (std::size_t i = 0; i < n; i++)
		{
			santaPositions.push_back({ 0, 0 });
		}

		std::size_t count = 0;

		for (const auto& step : source)
		{
			auto& current = santaPositions[count % n];

			current = current + stepMap.at(step);

			if (std::find(visited.cbegin(), visited.cend(), current) == visited.cend())
			{
				visited.push_back(current);
			}

			count++;
		}

		return std::to_string(visited.size());
	}

	std::string partOne(
			const std::string& inFilename)
	{
		return walkNSantas(inFilename, 1);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		return walkNSantas(inFilename, 2);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }
