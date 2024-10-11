#include "05.h"

#include <string>

#include "fileOps.h"


namespace advent { namespace y2015 { namespace d05
{
	bool threeVowels(
			const std::string& entry)
	{
		std::size_t count = 0;

		for (const auto& c : entry)
		{
			if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
			{
				count++;
			}
		}

		return count >= 3;
	}

	bool doubleLetter(
			const std::string& entry)
	{
		for (std::size_t i = 0; i < entry.size() - 1; i++)
		{
			if (entry.at(i) == entry.at(i + 1))
			{
				return true;
			}
		}

		return false;
	}

	bool naughtyWords(
			const std::string& entry)
	{
		std::vector<std::string> naughties { "ab", "cd", "pq", "xy" };

		for (const auto& naughty : naughties)
		{
			if (entry.find(naughty) != std::string::npos)
			{
				return false;
			}
		}

		return true;
	}

	bool isNicePartOne(
			const std::string& entry)
	{
		return threeVowels(entry) && doubleLetter(entry) && naughtyWords(entry);
	}
	
	bool doublePair(
			const std::string& entry)
	{
		for (std::size_t i = 0; i < entry.size() - 3; i++)
		{
			for (std::size_t j = i + 2; j < entry.size() - 1; j++)
			{
				if (entry.at(i) == entry.at(j) && entry.at(i + 1) == entry.at(j + 1))
				{
					return true;
				}
			}
		}
		return false;
	}

	bool spacedDouble(
			const std::string& entry)
	{
		for (std::size_t i = 0; i < entry.size() - 2; i++)
		{
			if (entry.at(i) == entry.at(i + 2))
			{
				return true;
			}
		}

		return false;
	}

	bool isNicePartTwo(
			const std::string& entry)
	{
		return doublePair(entry) && spacedDouble(entry);
	}

	std::string execute(
			const std::string& inFilename,
			std::function<bool(const std::string&)> niceFunction)
	{
		auto source = utility::fileOps::readFileToLines(inFilename);

		std::size_t niceCount = 0;

		for (const auto& line : source)
		{
			if (niceFunction(line))
			{
				niceCount++;
			}
		}

		return std::to_string(niceCount);
	}

	std::string partOne(
			const std::string& inFilename)
	{
		return execute(inFilename, isNicePartOne);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		return execute(inFilename, isNicePartTwo);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }

