#include "09.h"

#include <algorithm>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "combinatorics.h"
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

	std::tuple<std::map<std::pair<std::size_t, std::size_t>, std::size_t>, std::size_t> loadInput(
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

		std::map<std::string, std::size_t> locationIndices;

		for (std::size_t i = 0; i < locations.size(); i++)
		{
			locationIndices.emplace(std::make_pair(locations.at(i), i));
		}

		std::map<std::pair<std::size_t, std::size_t>, std::size_t> resultDistances;

		for (const auto& [ locationPair, distance ] : distances)
		{
			const auto& [ locationOne, locationTwo ] = locationPair;

			std::pair<std::size_t, std::size_t> indicesPair { locationIndices.at(locationOne), locationIndices.at(locationTwo) };

			resultDistances.emplace(std::make_pair(indicesPair, distance));
		}

		return { resultDistances, locations.size() };
	}

	std::string partOne(
			const std::string& inFilename)
	{
		auto [ distances, locationCount ] = loadInput(inFilename);

		auto perms = utility::combinatorics::permutations(locationCount);

		auto minDistance = std::numeric_limits<std::size_t>::max();

		for (const auto& row : perms)
		{
			std::size_t distance = 0;

			for (std::size_t i = 0; i < row.size() - 1; i++)
			{
				std::pair<std::size_t, std::size_t> entry { row.at(i), row.at(i + 1) };
				
				distance += distances.at(entry);
			}

			minDistance = minDistance > distance ? distance : minDistance;
		}

		return std::to_string(minDistance);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		auto [ distances, locationCount ] = loadInput(inFilename);

		auto perms = utility::combinatorics::permutations(locationCount);

		auto maxDistance = std::numeric_limits<std::size_t>::min();

		for (const auto& row : perms)
		{
			std::size_t distance = 0;

			for (std::size_t i = 0; i < row.size() - 1; i++)
			{
				std::pair<std::size_t, std::size_t> entry { row.at(i), row.at(i + 1) };
				
				distance += distances.at(entry);
			}

			maxDistance = maxDistance < distance ? distance : maxDistance;
		}

		return std::to_string(maxDistance);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }

