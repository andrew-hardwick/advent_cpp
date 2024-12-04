#include "04.h"

#include "fileOps.h"

#include <cstddef>
#include <string>


namespace advent { namespace y2024 { namespace d04
{

	bool findPattern(
			const std::vector<std::string>& data,
			const std::tuple<std::size_t, std::size_t>& position,
			const std::tuple<std::size_t, std::size_t>& patternDims,
			const std::vector<std::string>& pattern)
	{
		const auto& [ i, j ] = position;
		const auto& [ patternHeight, patternWidth ] = patternDims;

		for (std::size_t x = 0; x < patternHeight; x++)
		{
			for (std::size_t y = 0; y < patternWidth; y++)
			{
				if (pattern.at(x).at(y) == '.')
					continue;

				if (data.at(i + x).at(j + y) != pattern.at(x).at(y))
					return false;
			}
		}

		return true;
	}

	std::size_t countOccurrences(
			const std::vector<std::string>& data,
			const std::vector<std::vector<std::string>>& patterns)
	{
		std::size_t result = 0;

		for (const auto& pattern : patterns)
		{
			auto patternHeight = pattern.size();
			auto patternWidth = pattern.at(0).size();

			std::tuple<std::size_t, std::size_t> patternDims { patternHeight, patternWidth };

			auto dataHeight = data.size() - (patternHeight - 1);
			auto dataWidth = data.at(0).size() - (patternWidth - 1);

			for (std::size_t i = 0; i < dataHeight; i++)
			{
				for (std::size_t j = 0; j < dataWidth; j++)
				{
					if (findPattern(data, { i, j }, patternDims, pattern))
						result++;
				}
			}
		}

		return result;
	}

	std::string partOne(
			const std::string& inFilename)
	{
		auto data = utility::fileOps::readFileToLines(inFilename);

		std::vector<std::vector<std::string>> patterns { 
			{ "X", "M", "A", "S" },
			{ "S", "A", "M", "X" },
			{ "XMAS" },
			{ "SAMX" },
			{ "X...", ".M..", "..A.", "...S" },
			{ "S...", ".A..", "..M.", "...X" },
			{ "...X", "..M.", ".A..", "S..." },
			{ "...S", "..A.", ".M..", "X..." }
		};

		auto result = countOccurrences(data, patterns);

		return std::to_string(result);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		auto data = utility::fileOps::readFileToLines(inFilename);

		std::vector<std::vector<std::string>> patterns { 
			{ "M.M", ".A.", "S.S" },
			{ "S.M", ".A.", "S.M" },
			{ "S.S", ".A.", "M.M" },
			{ "M.S", ".A.", "M.S" }
		};

		auto result = countOccurrences(data, patterns);

		return std::to_string(result);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }
