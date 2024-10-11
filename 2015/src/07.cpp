#include "07.h"

#include "adventTypedef.h"
#include "fileOps.h"
#include "stringUtils.h"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <utility>
#include <vector>


namespace advent { namespace y2015 { namespace d07
{
	enum class Operator { NOOP, NOT, AND, OR, LSHIFT, RSHIFT };

	Operator stoop(
			const std::string& source)
	{
		if ("NOOP" == source)
			return Operator::NOOP;
		if ("NOT" == source)
			return Operator::NOT;
		if ("AND" == source)
			return Operator::AND;
		if ("OR" == source)
			return Operator::OR;
		if ("LSHIFT" == source)
			return Operator::LSHIFT;
		if ("RSHIFT" == source)
			return Operator::RSHIFT;

		throw std::invalid_argument("Encountered unknown operator string");
	}

	struct WireNode
	{
		std::vector<std::string> operands;
		Operator op;
	};

	bool isDigits(
			const std::string &str)
	{
		return std::all_of(str.begin(), str.end(), ::isdigit);
	}

	std::optional<WireNode> parseNonary(
			const std::string& lValue,
			const std::string& target,
			std::map<std::string, uint16_t>& cache)
	{
		if (isDigits(lValue))
		{
			uint16_t value { (uint16_t)std::stoi(lValue) };

			cache.emplace(std::make_pair(lValue, value));

			if (lValue != target)
			{
				cache.emplace(std::make_pair(target, value));
			}

			return std::nullopt;
		}
		else
		{
			WireNode node { { lValue }, Operator::NOOP };

			return node;
		}
	}

	std::optional<WireNode> parseUnary(
			const std::vector<std::string>& lValues,
			std::map<std::string, uint16_t>& cache)
	{
		if (lValues.at(0) == "NOT")
		{
			WireNode node { { lValues.at(1) }, Operator::NOT };

			auto _ = parseNonary(lValues.at(1), lValues.at(1), cache);

			return node;
		}
		else
		{
			throw std::invalid_argument("Unexpected unary operation");
		}
	}

	std::optional<WireNode> parseBinary(
			const std::vector<std::string>& lValues,
			std::map<std::string, uint16_t>& cache)
	{
		std::vector<std::string> operands { lValues.at(0), lValues.at(2) };

		auto op = stoop(lValues.at(1));
		WireNode node { operands, op };

		for (const auto& operand : operands)
		{
			auto _ = parseNonary(operand, operand, cache);
		}

		return node;
	}

	std::tuple<std::map<std::string, WireNode>, std::map<std::string, uint16_t>> loadInput(
			const std::string& inFilename)
	{
		auto lines = utility::fileOps::readFileToLines(inFilename);

		std::map<std::string, WireNode> nodes;
		std::map<std::string, uint16_t> cache;

		for (const auto& line : lines)
		{
			auto splitLine = utility::string::split(line, " -> ");

			auto lValues = utility::string::split(splitLine[0], " ");
			auto target = splitLine[1];

			std::optional<WireNode> result;

			if (lValues.size() == 1)
			{
				result = parseNonary(lValues.at(0), target, cache);
			}
			else if (lValues.size() == 2)
			{
				result = parseUnary(lValues, cache);
			}
			else if (lValues.size() == 3)
			{
				result = parseBinary(lValues, cache);
			}
			else
			{
				throw std::invalid_argument("encountered unexpected lValue length");
			}

			if (result.has_value())
			{
				nodes.emplace(std::make_pair(target, result.value()));
			}
		}

		return { nodes, cache };
	}

	uint16_t executeNode(
			const WireNode& node,
			const std::vector<uint16_t>& operands,
			std::map<std::string, uint16_t>& cache)
	{
		switch (node.op)
		{
			case Operator::NOOP:
				return operands.at(0);
			case Operator::NOT:
				return ~operands.at(0);
			case Operator::AND:
				return operands.at(0) & operands.at(1);
			case Operator::OR:
				return operands.at(0) | operands.at(1);
			case Operator::LSHIFT:
				return operands.at(0) << operands.at(1);
			case Operator::RSHIFT:
				return operands.at(0) >> operands.at(1);
		}

		throw std::invalid_argument("Encountered unexpected operator");
	}

	uint16_t getValue(
			const std::string& target,
			const std::map<std::string, WireNode> wireMap,
			std::map<std::string, uint16_t>& cache)
	{
		if (cache.find(target) != cache.end())
		{
			return cache.at(target);
		}
		
		auto node = wireMap.at(target);

		std::vector<uint16_t> operands;

		for (const auto& operand : node.operands)
		{
			uint16_t opValue = getValue(operand, wireMap, cache);

			operands.push_back(opValue);
		}

		auto value = executeNode(node, operands, cache);
				
		cache.emplace(std::make_pair(target, value));

		return value;
	}

	std::string partOne(
			const std::string& inFilename)
	{
		auto [ wireMap, cache ] = loadInput(inFilename);

		auto result = getValue("a", wireMap, cache);

		return std::to_string(result);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		auto [ wireMap, cache ] = loadInput(inFilename);

		auto a = getValue("a", wireMap, cache);

		auto [ wireMap2, cache2 ] = loadInput(inFilename);

		if (cache2.find("b") != cache2.end())
		{
			cache2["b"] = a;
		}
		else
		{
			cache2.emplace(std::make_pair("b", a));
		}

		auto result = getValue("a", wireMap2, cache2);

		return std::to_string(result);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }
