#include "18.h"

#include "fileOps.h"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

#define STEP_COUNT 100


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

		const auto& [ maxY, maxX ] = extents;
		const auto& [ curY, curX ] = location;

		if (curY > 0)
		{
			if (curX > 0)
				if (map[curY - 1][curX - 1])
					result++;
			if (curX < maxX - 1)
				if (map[curY - 1][curX + 1])
					result++;
			if (map[curY - 1][curX]) result++;
		}
		if (curY < maxY - 1)
		{
			if (curX > 0)
				if (map[curY + 1][curX - 1])
					result++;
			if (curX < maxX - 1)
				if (map[curY + 1][curX + 1])
					result++;
			if (map[curY + 1][curX]) result++;
		}
		if (curX > 0)
			if (map[curY][curX - 1]) result++;
		if (curX < maxX - 1)
			if (map[curY][curX + 1]) result++;

		return result;
	}

	void lightCorners(
			std::vector<std::vector<bool>>& map,
			const std::tuple<std::size_t, std::size_t>& extents)
	{
		const auto& [ height, width ] = extents;

		map[0][0] = true;
		map[0][width - 1] = true;
		map[height - 1][0] = true;
		map[height - 1][width - 1] = true;
	}

	std::vector<std::vector<bool>> step(
			const std::vector<std::vector<bool>>& map,
			const std::tuple<std::size_t, std::size_t>& extents,
			bool cornersLit)
	{
		const auto& [ height, width ] = extents;

		std::vector<std::vector<bool>> result;

		for (std::size_t y = 0; y < height; y++)
		{
			std::vector<bool> resultRow;

			for (std::size_t x = 0; x < width; x++)
			{
				auto liveNeighbors = countLiveNeighbors(map, extents, { y, x });

				auto current = map.at(y).at(x);

				if (current && !(liveNeighbors == 2 || liveNeighbors == 3))
					current = false;
				else if (!current && liveNeighbors == 3)
					current = true;

				resultRow.push_back(current);
			}

			result.push_back(resultRow);
		}

		if (cornersLit)
		{
			lightCorners(result, extents);
		}

		return result;
	}

	std::size_t countLit(
			const std::vector<std::vector<bool>>& map)
	{
		std::size_t result = 0;

		for (const auto& row : map)
		{
			for (const auto& val : row)
			{
				if (val) result++;
			}
		}

		return result;
	}

	void printMap(
			const std::vector<std::vector<bool>>& map)
	{
		for (const auto& row : map)
		{
			for (const auto& val : row)
			{
				if (val)
					std::cout << "#";
				else
					std::cout << ".";
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	void printLiveNeighbors(
			const std::vector<std::vector<bool>>& map,
			const std::tuple<std::size_t, std::size_t>& extents)
	{
		const auto& [ maxY, maxX ] = extents;

		for (std::size_t y = 0; y < maxY; y++)
		{
			for (std::size_t x = 0; x < maxX; x++)
			{
				auto live = countLiveNeighbors(map, extents, { y, x });
				
				if (live == 0)
					std::cout << '.';
				else
					std::cout << live;
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}

	std::string partOne(
			const std::string& inFilename)
	{
		auto map = loadInput(inFilename);

		auto extents = getExtents(map);

		for (std::size_t i = 0; i < STEP_COUNT; i++)
			map = step(map, extents, false);

		auto result = countLit(map);

		return std::to_string(result);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		auto map = loadInput(inFilename);

		auto extents = getExtents(map);

		lightCorners(map, extents);

		for (std::size_t i = 0; i < STEP_COUNT; i++)
			map = step(map, extents, true);

		auto result = countLit(map);

		return std::to_string(result);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }
