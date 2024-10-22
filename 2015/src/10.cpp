#include "10.h"
#include <iostream>
#include <string>

#include "fileOps.h"


namespace advent { namespace y2015 { namespace d10
{
	std::vector<std::size_t> step(
			const std::vector<std::size_t>& source)
	{
		std::vector<std::size_t> result;

		auto previous = source.at(0);
		std::size_t count = 1;

		for (std::size_t i = 1; i < source.size(); i++)
		{
			auto current = source.at(i);

			if (previous == current)
			{
				count++;
			}
			else
			{
				result.push_back(count);
				result.push_back(previous);

				previous = current;
				count = 1;
			}
		}

		result.push_back(count);
		result.push_back(previous);

		return result;
	}

	std::vector<std::size_t> loadInput(
			const std::string& inFilename)
	{
		std::vector<std::size_t> result;

		auto source = utility::fileOps::readFileToChars(inFilename);

		for (const auto& c : source)
		{
			result.push_back((int)c - 48);
		}

		return result;
	}

	std::string execute(
			const std::string& inFilename,
			std::size_t iterations)
	{
		auto working = loadInput(inFilename);
		
		for (std::size_t i = 0; i < iterations; i++)
		{
			working = step(working);
		}

		auto result = working.size();

		return std::to_string(result);
	}

	std::string partOne(
			const std::string& inFilename)
	{
		return execute(inFilename, 40);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		return execute(inFilename, 50);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }

