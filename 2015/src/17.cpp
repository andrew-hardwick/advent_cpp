#include "17.h"

#include "fileOps.h"
#include "vectorMath.h"

#include <algorithm>
#include <string>

#define EGGNOG 150


namespace advent { namespace y2015 { namespace d17
{
	int parseLine(
			const std::string& line)
	{
		return std::stoi(line);
	}

	std::vector<int> loadInput(
			const std::string& inFilename)
	{
		auto source = utility::fileOps::readFileToLines(inFilename);

		std::vector<int> result(source.size());

		std::transform(source.cbegin(), source.cend(), result.begin(), parseLine);

		std::sort(result.begin(), result.end());

		return result;
	}

	void countValidCombinations(
			const std::vector<int>& source,
			int target,
			std::size_t startIndex,
			std::vector<int>& selected,
			std::vector<std::size_t>& validCounts)
	{
		auto total = utility::vectorMath::sum(selected);

		if (total > target)
			return;
		if (total == target)
		{
			validCounts.push_back(selected.size());
			return;
		}

		for (std::size_t i = startIndex; i < source.size(); i++)
		{
			auto v = source.at(i);

			selected.push_back(v);

			countValidCombinations(source, target, i + 1, selected, validCounts);

			selected.pop_back();
		}
	}

	std::string partOne(
			const std::string& inFilename)
	{
		auto source = loadInput(inFilename);

		std::vector<int> selected;
		std::vector<std::size_t> validCounts;

		countValidCombinations(source, EGGNOG, 0, selected, validCounts);

		auto validCount = validCounts.size();

		return std::to_string(validCount);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		auto source = loadInput(inFilename);

		std::vector<int> selected;
		std::vector<std::size_t> validCounts;

		countValidCombinations(source, EGGNOG, 0, selected, validCounts);

		auto validCount = 0;

		auto minCount = *std::min_element(validCounts.cbegin(), validCounts.cend());

		for (const auto& e : validCounts)
		{
			if (e == minCount)
				validCount++;
		}

		return std::to_string(validCount);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }
