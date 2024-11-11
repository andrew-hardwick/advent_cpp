#include "13.h"

#include "combinatorics.h"
#include "fileOps.h"
#include "stringUtils.h"

#include <algorithm>
#include <limits>
#include <string>
#include <utility>


namespace advent { namespace y2015 { namespace d13
{
	struct relationship_t
	{
		std::string person;
		std::string neighbor;
		int happiness;
	};

	relationship_t parseLine(
			const std::string& line)
	{
		std::vector<std::string> targets { " would ", " gain ", " lose ", " happiness units by sitting next to ", "." };
		std::vector<std::string> replacements { " ", " ", " -", " ", "" };

		auto cleanedLine = utility::string::replace(line, targets, replacements);

		auto split = utility::string::split(cleanedLine, " ");

		return { split[0], split[2], std::stoi(split[1]) };
	}

	std::vector<relationship_t> loadInput(
			const std::string& inFilename)
	{
		std::vector<relationship_t> result;

		auto source = utility::fileOps::readFileToLines(inFilename);

		for (const auto& line : source)
		{
			result.push_back(parseLine(line));
		}

		return result;
	}

	std::vector<std::string> getUniqueNames(
			const std::vector<relationship_t>& source)
	{
		std::vector<std::string> result;

		for (const auto& [ name, _0, _1 ] : source)
		{
			if (std::find(result.cbegin(), result.cend(), name) == result.cend())
			{
				result.push_back(name);
			}
		}

		return result;
	}

	void appendHappiness(
			const std::string& personOne,
			const std::string& personTwo,
			int happiness,
			std::map<std::pair<std::string, std::string>, int>& happinessMap)
	{
		auto key = std::make_pair(personOne, personTwo);

		if (happinessMap.find(key) == happinessMap.end())
		{
			happinessMap.emplace(std::make_pair(key, 0));
		}

		happinessMap.at(key) += happiness;
	}

	std::map<std::pair<std::string, std::string>, int> getHappinessMap(
			const std::vector<relationship_t>& source)
	{
		std::map<std::pair<std::string, std::string>, int> result;

		for (const auto& [ personA, personB, happiness ] : source)
		{
			appendHappiness(personA, personB, happiness, result);
			appendHappiness(personB, personA, happiness, result);
		}

		return result;
	}

	int evaluatePermutation(
			const std::map<std::pair<std::string, std::string>, int>& happinessMap,
			const std::vector<std::string>& uniqueNames,
			const std::vector<std::size_t>& permutation)
	{
		auto result = 0;

		for (std::size_t i = 0; i < permutation.size(); i++)
		{
			auto nextIndex = i < permutation.size() - 1 ? i + 1 : 0;

			auto personA = uniqueNames.at(permutation.at(i));
			auto personB = uniqueNames.at(permutation.at(nextIndex));

			auto key = std::make_pair(personA, personB);

			result += happinessMap.at(key);
		}

		return result;
	}
	
	int findBestPermutation(
			const std::map<std::pair<std::string, std::string>, int>& happinessMap,
			const std::vector<std::string>& uniqueNames,
			const std::vector<std::vector<std::size_t>>& permutations)
	{
		int best = std::numeric_limits<int>::min();

		for (const auto& permutation : permutations)
		{
			auto current = evaluatePermutation(happinessMap, uniqueNames, permutation);

			best = std::max(best, current);
		}

		return best;
	}

	std::string partOne(
			const std::string& inFilename)
	{
		auto source = loadInput(inFilename);

		auto happinessMap = getHappinessMap(source);

		auto uniqueNames = getUniqueNames(source);

		auto permutations = utility::combinatorics::permutations(uniqueNames.size());

		auto result = findBestPermutation(happinessMap, uniqueNames, permutations);

		return std::to_string(result);
	}

	void addSelf(
			std::vector<relationship_t>& source,
			std::vector<std::string>& names)
	{
		for (const auto& name : names)
		{
			relationship_t newRelationshipOne { "self", name, 0 };
			relationship_t newRelationshipTwo { "self", name, 0 };

			source.push_back(newRelationshipOne);
			source.push_back(newRelationshipTwo);
		}

		names.push_back("self");
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		auto source = loadInput(inFilename);

		auto uniqueNames = getUniqueNames(source);

		addSelf(source, uniqueNames);

		auto happinessMap = getHappinessMap(source);

		auto permutations = utility::combinatorics::permutations(uniqueNames.size());

		auto result = findBestPermutation(happinessMap, uniqueNames, permutations);

		return std::to_string(result);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }

