#include "18.h"

#include "fileOps.h"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

#define STEP_COUNT 4


namespace advent { namespace y2015 { namespace d18
{
	bool parseChar(
			char c)
	{
		if (c == '#')
			return true;

		return false;
	}

	std::vector<bool> parseLine(
			const std::string& line)
	{
		std::vector<bool> result(line.size());

		std::transform(line.cbegin(), line.cend(), result.begin(), parseChar);

		return result;
	}

	std::vector<std::vector<bool>> loadInput(
			const std::string& inFilename)
	{
		auto source = utility::fileOps::readFileToLines(inFilename);

		std::vector<std::vector<bool>> result(source.size());

		std::transform(source.cbegin(), source.cend(), result.begin(), parseLine);

		return result;
	}

	std::tuple<std::size_t, std::size_t> getExtents(
			const std::vector<std::vector<bool>>& map)
	{
		auto height = map.size();

		auto width = map.at(0).size();

		for (const auto& row : map)
		{
			if (row.size() != width)
				throw std::invalid_argument("Map must be square");
		}

		return { height, width };
	}

	std::size_t countLiveNeighbors(
			const std::vector<std::vector<bool>>& map,
			const std::tuple<std::size_t, std::size_t>& extents,
			const std::tuple<std::size_t, std::size_t>& location)
	{
		std::size_t result = 0;


		return result;
	}

	void step(
			std::vector<std::vector<bool>>& map,
			const std::tuple<std::size_t, std::size_t>& extents,
			bool cornersLit)
	{
		const auto& [ height, width ] = extents;

		for (std::size_t y = 0; y < height; y++)
		{
			for (std::size_t x = 0; x < width; x++)
			{
				auto liveNeighbors = countLiveNeighbors(map, extents, { y, x });

				auto current = map.at(y).at(x);

				if (current && liveNeighbors != 2 && liveNeighbors != 3)
					map.at(y).at(x) = false;
				if (!current && liveNeighbors == 3)
					map.at(y).at(x) = true;
			}
		}
	}

	void printMap(
			const std::vector<std::vector<bool>>& map)
	{
		std::cout << "\n";
		for (const auto& row : map)
		{
			for (const auto& v : row)
			{
				if (v)
					std::cout << "#";
				else
					std::cout << ".";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	std::size_t countLit(
			const std::vector<std::vector<bool>>& map)
	{
		return 0;
	}

	std::string partOne(
			const std::string& inFilename)
	{
		auto map = loadInput(inFilename);

		auto extents = getExtents(map);

		printMap(map);

		for (std::size_t i = 0; i < STEP_COUNT; i++)
		{
			step(map, extents, false);
			printMap(map);
		}

		auto result = countLit(map);

		return std::to_string(result);
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
