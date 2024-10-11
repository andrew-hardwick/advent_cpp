#include "06.h"

#include <string>

#include <iostream>

#include "fileOps.h"
#include "point.h"
#include "stringUtils.h"

#define WIDTH_201506 1000


namespace advent { namespace y2015 { namespace d06
{
	enum class Command { TURN_ON, TURN_OFF, TOGGLE };

	struct Instruction
	{
		Command command;
		utility::Point p1;
		utility::Point p2;
	};

	Command parseCommand(
			const std::string& source)
	{
		if ("on" == source)
			return Command::TURN_ON;
		else if ("off" == source)
			return Command::TURN_OFF;
		else
			return Command::TOGGLE;
	}

	Instruction parseInstruction(
			const std::string& source)
	{
		std::vector<std::string> targets { ",", " through ", "turn " };
		std::vector<std::string> replacements { " ", " ", "" };

		auto clean = utility::string::replace(source, targets, replacements);

		auto split = utility::string::split(clean, " ");

		Command command { parseCommand(split.at(0)) };

		split.erase(split.begin());

		auto indices = utility::string::convertToIntArray(split);

		return { command, { indices.at(0), indices.at(1) }, { indices.at(2), indices.at(3) } };
	}

	std::vector<Instruction> loadInput(
			const std::string& inFilename)
	{
		auto source = utility::fileOps::readFileToLines(inFilename);

		std::vector<Instruction> result;

		for (const auto& entry : source)
		{
			result.push_back(parseInstruction(entry));
		}

		return result;
	}

	int* getBlankMap()
	{
		std::size_t length = WIDTH_201506 * WIDTH_201506;

		int* result = (int*) malloc(length * sizeof(int));

		for (std::size_t i = 0; i < length; i++)
		{
			result[i] = false;
		}

		return result;
	}

	void executeInstructionPartOne(
			int* map,
			Instruction instruction)
	{
		const auto& [ command, p1, p2 ] = instruction;
		const auto& [ x1, y1 ] = p1;
		const auto& [ x2, y2 ] = p2;

		std::function<int(int)> op;

		switch (command)
		{
			case Command::TURN_ON:
				op = [] (int v) { return 1; };
				break;
			case Command::TURN_OFF:
				op = [] (int v) { return 0; };
				break;
			case Command::TOGGLE:
				op = [] (int v) { return 1 - v; };
				break;
		}

		for (auto x = x1; x <= x2; x++)
		{
			for (auto y = y1; y <= y2; y++)
			{
				std::size_t index = x * WIDTH_201506 + y;

				*(map + index) = op(*(map + index));
			}
		}
	}

	void executeInstructionPartTwo(
			int* map,
			Instruction instruction)
	{
		const auto& [ command, p1, p2 ] = instruction;
		const auto& [ x1, y1 ] = p1;
		const auto& [ x2, y2 ] = p2;

		std::function<int(int)> op;

		switch (command)
		{
			case Command::TURN_ON:
				op = [] (int v) { return v + 1; };
				break;
			case Command::TURN_OFF:
				op = [] (int v) 
				{
					if (v == 0)
						return 0;
					return v - 1;
				};
				break;
			case Command::TOGGLE:
				op = [] (int v) { return v + 2; };
				break;
		}

		for (auto x = x1; x <= x2; x++)
		{
			for (auto y = y1; y <= y2; y++)
			{
				std::size_t index = x * WIDTH_201506 + y;

				*(map + index) = op(*(map + index));
			}
		}
	}

	std::size_t countLit(
			int* map)
	{
		std::size_t length = WIDTH_201506 * WIDTH_201506;

		std::size_t count = 0;

		for (std::size_t i = 0; i < length; i++)
		{
			count += *(map + i);
		}

		return count;
	}

	std::string partOne(
			const std::string& inFilename)
	{
		auto instructions = loadInput(inFilename);

		auto map = getBlankMap();

		for (const auto& instruction : instructions)
		{
			executeInstructionPartOne(map, instruction);
		}

		auto count = countLit(map);

		free(map);

		return std::to_string(count);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		auto instructions = loadInput(inFilename);

		auto map = getBlankMap();

		for (const auto& instruction : instructions)
		{
			executeInstructionPartTwo(map, instruction);
		}

		auto count = countLit(map);

		free(map);

		return std::to_string(count);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }

