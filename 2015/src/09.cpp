#include "09.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

#include "fileOps.h"
#include "stringUtils.h"


namespace advent { namespace y2015 { namespace d09
{
	std::tuple<std::string, std::string, std::size_t> parseLine(
			const std::string& line)
	{
		std::vector<std::string> replaceTargets { " to ", " = " };
		std::vector<std::string> replaceResults { " ", " " };

		auto cleaned = utility::string::replace(line, replaceTargets, replaceResults);

		auto splitLine = utility::string::split(cleaned, " ");

		return { splitLine.at(0), splitLine.at(1), std::stoi(splitLine.at(2)) };
	}

	std::tuple<std::map<std::pair<std::string, std::string>, std::size_t>, std::vector<std::string>> loadInput(
			const std::string& inFilename)
	{
		std::map<std::pair<std::string, std::string>, std::size_t> distances;
		std::vector<std::string> locations;

		auto lines = utility::fileOps::readFileToLines(inFilename);

		for (const auto& line : lines)
		{
			auto [ loc1, loc2, distance ] = parseLine(line);

			distances.emplace(std::make_pair(std::make_pair(loc1, loc2), distance));
			distances.emplace(std::make_pair(std::make_pair(loc2, loc1), distance));

			if (std::find(locations.begin(), locations.end(), loc1) == locations.end())
			{
				locations.push_back(loc1);
			}

			if (std::find(locations.begin(), locations.end(), loc2) == locations.end())
			{
				locations.push_back(loc2);
			}
		}

		return { distances, locations };
	}

	std::string partOne(
			const std::string& inFilename)
	{
		auto [ distances, locations ] = loadInput(inFilename);

		for (const auto& loc : locations)
		{
			std::cout << loc << "\n";
		}
		return "nonimpl";
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		return "nonimpl";
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }

