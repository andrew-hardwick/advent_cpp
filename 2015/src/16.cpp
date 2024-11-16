#include "16.h"

#include "fileOps.h"
#include "stringUtils.h"

#include <algorithm>
#include <functional>
#include <string>
#include <utility>


namespace advent { namespace y2015 { namespace d16
{
	struct auntSue_t
	{
		int auntieNumber = -1;
		std::map<std::string, int> properties;
	};

	auntSue_t getPrototypeAunt()
	{
		auntSue_t prototype;

		prototype.properties.emplace(std::make_pair("children", 3));
		prototype.properties.emplace(std::make_pair("cats", 7));
		prototype.properties.emplace(std::make_pair("samoyeds", 2));
		prototype.properties.emplace(std::make_pair("pomeranians", 3));
		prototype.properties.emplace(std::make_pair("akitas", 0));
		prototype.properties.emplace(std::make_pair("vizslas", 0));
		prototype.properties.emplace(std::make_pair("goldfish", 5));
		prototype.properties.emplace(std::make_pair("trees", 3));
		prototype.properties.emplace(std::make_pair("cars", 2));
		prototype.properties.emplace(std::make_pair("perfumes", 1));

		return prototype;
	}

	auntSue_t parseLine(
			const std::string& line)
	{
		auntSue_t result;

		std::vector<std::string> targets { "Sue ", ": ", ", " };
		std::vector<std::string> replacements { "", " ", " " };

		auto cleaned = utility::string::replace(line, targets, replacements);
		auto split = utility::string::split(cleaned, " ");

		result.auntieNumber = std::stoi(split[0]);

		for (std::size_t i = 1; i < split.size(); i += 2)
		{
			auto field = split[i];
			auto value = std::stoi(split[i + 1]);

			result.properties.emplace(std::make_pair(field, value));
		}

		return result;
	}

	std::vector<auntSue_t> loadInput(
			const std::string& inFilename)
	{
		auto source = utility::fileOps::readFileToLines(inFilename);

		std::vector<auntSue_t> result(source.size());

		std::transform(source.cbegin(), source.cend(), result.begin(), parseLine);

		return result;
	}

	bool checkAuntPartOne(
			const auntSue_t& prototype,
			const auntSue_t& auntSue)
	{
		for (const auto& [ key, value ] : auntSue.properties)
		{
			if (prototype.properties.at(key) != value)
				return false;
		}

		return true;
	}

	bool checkAuntPartTwo(
			const auntSue_t& prototype,
			const auntSue_t& auntSue)
	{
		for (const auto& [ key, value ] : auntSue.properties)
		{
			if (key == "cats" || key == "trees")
			{
				if (prototype.properties.at(key) >= value)
					return false;
			}
			else if (key == "pomeranians" || key == "goldfish")
			{
				if (prototype.properties.at(key) <= value)
					return false;
			}
			else
			{
				if (prototype.properties.at(key) != value)
					return false;
			}
		}

		return true;
	}

	std::size_t findMatchingAunt(
			const auntSue_t prototype,
			const std::vector<auntSue_t>& aunts,
			std::function<bool(const auntSue_t&, const auntSue_t&)> isValidAunt)
	{
		for (std::size_t i = 0; i < aunts.size(); i++)
		{
			if (isValidAunt(prototype, aunts[i]))
					return i + 1;
		}

		return 10000;
	}

	std::string partOne(
			const std::string& inFilename)
	{
		auto source = loadInput(inFilename);

		auto prototype = getPrototypeAunt();

		auto result = findMatchingAunt(prototype, source, checkAuntPartOne);

		return std::to_string(result);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		auto source = loadInput(inFilename);

		auto prototype = getPrototypeAunt();

		auto result = findMatchingAunt(prototype, source, checkAuntPartTwo);

		return std::to_string(result);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }
