#include "03.h"

#include "fileOps.h"
#include "stringUtils.h"

#include <regex>
#include <string>


namespace advent { namespace y2024 { namespace d03
{
	enum class InstructionType { UNKNOWN, DO, DONT, MUL };

	std::tuple<std::string, std::size_t, std::string> findInstruction(
			const std::string& source,
			const std::regex& pattern)
	{
		std::smatch m;

		if (!std::regex_search(source, m, pattern))
			return { "", -1, source };

		int split_index = m.position();
		int length = m.length();

		return { source.substr(split_index, length), split_index, source.substr(split_index + length) };
	}

	std::tuple<std::string, InstructionType, std::string> findNextWholeInstruction(
			const std::string& source)
	{
		std::vector<std::tuple<std::regex, InstructionType>> patterns {
			{ std::regex("mul\\([0-9]+,[0-9]+\\)"), InstructionType::MUL },
			{ std::regex("do\\(\\)"), InstructionType::DO },
			{ std::regex("don't\\(\\)"), InstructionType::DONT }
		};

		std::size_t firstIndex = -1;
		std::string firstMatch = "";
		std::string resultSource = "";
		InstructionType resultType = InstructionType::UNKNOWN;

		for (const auto& [ pattern, type ] : patterns)
		{
			const auto& [ match, index, candidateSource ] = findInstruction(source, pattern);

			if (index == (std::size_t)(-1))
				continue;

			if (index < firstIndex)
			{
				firstIndex = index;
				firstMatch = match;
				resultSource = candidateSource;
				resultType = type;
			}
		}

		return { firstMatch, resultType, resultSource };
	}

	int processMul(
			const std::string& instruction)
	{
		std::vector<std::string> targets { "mul(", ")" };
		std::vector<std::string> replacements { "", "" };

		auto clean = utility::string::replace(instruction, targets, replacements);

		auto numbers = utility::string::parseToIntArray(clean, ",");

		return numbers[0] * numbers[1];
	}

	int processNumericInstruction(
			InstructionType type,
			const std::string& instruction)
	{
		switch (type)
		{
			case InstructionType::MUL:
				return processMul(instruction);
			default:
				return 0;
		}
	}

	std::string partOne(
			const std::string& inFilename)
	{
		auto source = utility::fileOps::readFileRaw(inFilename);

		std::string instruction = "non-empty";
		InstructionType type = InstructionType::UNKNOWN;

		int result = 0;

		do
		{
			std::tie(instruction, type, source) = findNextWholeInstruction(source);

			if (type == InstructionType::MUL)
				result += processNumericInstruction(type, instruction);
		} while (instruction.size() > 0);

		return std::to_string(result);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		auto source = utility::fileOps::readFileRaw(inFilename);

		std::string instruction = "non-empty";
		InstructionType type = InstructionType::UNKNOWN;

		bool enabled = true;

		int result = 0;

		do
		{
			std::tie(instruction, type, source) = findNextWholeInstruction(source);

			if (type == InstructionType::DO)
				enabled = true;
			if (type == InstructionType::DONT)
				enabled = false;
			if (type == InstructionType::MUL && enabled)			
				result += processNumericInstruction(type, instruction);
		} while (instruction.size() > 0);

		return std::to_string(result);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }
