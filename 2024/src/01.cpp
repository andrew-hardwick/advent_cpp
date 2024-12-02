#include "01.h"

#include <algorithm>
#include <cmath>
#include <string>

#include "fileOps.h"
#include "stringUtils.h"


namespace advent { namespace y2024 { namespace d01
{
	std::tuple<std::size_t, std::size_t> parseLine(
			const std::string& line)
	{
		auto split = utility::string::split(line, "   ");

		std::size_t valOne = std::stoi(split[0]);
		std::size_t valTwo = std::stoi(split[1]);

		return { valOne, valTwo };
	}

	std::tuple<std::vector<std::size_t>, std::vector<std::size_t>> load_input(
			const std::string& inFilename)
	{
		auto source = utility::fileOps::readFileToLines(inFilename);

		std::vector<std::size_t> listOne;
		std::vector<std::size_t> listTwo;

		for (const auto& line : source)
		{
			auto [ newOne, newTwo ] = parseLine(line);

			listOne.push_back(newOne);
			listTwo.push_back(newTwo);
		}

		return { listOne, listTwo };
	}

	std::string partOne(
			const std::string& inFilename)
	{
		auto [ listOne, listTwo ] = load_input(inFilename);

		std::sort(listOne.begin(), listOne.end());
		std::sort(listTwo.begin(), listTwo.end());

		std::size_t result = 0;

		for (std::size_t i = 0; i < listOne.size(); i++)
		{
			auto delta = std::abs((int)(listOne.at(i) - listTwo.at(i)));

			result += delta;
		}

		return std::to_string(result);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		auto [ listOne, listTwo ] = load_input(inFilename);

		std::map<std::size_t, std::size_t> countCache;

		std::size_t result = 0;

		for (const auto& val : listOne)
		{
			if (countCache.find(val) == countCache.end())
			{
				auto count = std::count(listTwo.begin(), listTwo.end(), val);

				countCache.emplace(std::make_pair(val, val * count));
			}

			result += countCache.at(val);
		}

		return std::to_string(result);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }
