#include "05.h"

#include "fileOps.h"
#include "stringUtils.h"

#include <string>


namespace advent { namespace y2024 { namespace d05
{
	using pageOrders_t = std::vector<std::tuple<int, int>>;
	using updates_t = std::vector<std::vector<int>>;

	std::tuple<pageOrders_t, updates_t> loadInput(
			const std::string& inFilename)
	{
		pageOrders_t resultOrders;
		updates_t resultUpdates;

		auto source = utility::fileOps::readFileToLines(inFilename);

		for (const auto& line : source)
		{
			if(line.find("|") != std::string::npos)
			{
				auto split = utility::string::split(line, "|");

				auto first = std::stoi(split[0]);
				auto second = std::stoi(split[1]);

				resultOrders.push_back({ first, second });
			}
			else if (line.find(",") != std::string::npos)
			{
				auto update = utility::string::parseToIntArray(line, ",");

				resultUpdates.push_back(update);
			}
		}

		return { resultOrders, resultUpdates };
	}


	bool isValidUpdate(
			const pageOrders_t& orders,
			const std::vector<int>& update)
	{
		for (const auto& [ first, second ] : orders)
		{
			auto firstIt = std::find(update.cbegin(), update.cend(), first);

			if (firstIt == update.cend())
				continue;

			auto secondIt = std::find(update.cbegin(), update.cend(), second);

			if (firstIt > secondIt)
				return false;
		}

		return true;
	}

	std::function<bool(int, int)> createComparator(
			const pageOrders_t& orders)
	{
		auto functor = [ orders = std::move(orders) ] (int a, int b)
		{
			for (const auto& [ first, second ] : orders)
			{
				if (first == b && second == a)
				{
					return true;
				}
			}

			return false;
		};

		return functor;
	}

	int getMiddleValue(
			const std::vector<int>& update)
	{
		auto middleIndex = update.size() / 2;

		return update.at(middleIndex);
	}

	std::string partOne(
			const std::string& inFilename)
	{
		const auto& [ orders, updates ] = loadInput(inFilename);

		int result = 0;

		for (const auto& update : updates)
		{
			if (isValidUpdate(orders, update))
				result += getMiddleValue(update);
		}

		return std::to_string(result);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		const auto& [ orders, updates ] = loadInput(inFilename);

		int result = 0;

		auto comparator = createComparator(orders);

		for (auto update : updates)
		{
			if (isValidUpdate(orders, update))
				continue;

			std::sort(update.begin(), update.end(), comparator);

			result += getMiddleValue(update);
		}

		return std::to_string(result);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }
