#include "15.h"

#include <cstddef>
#include <limits>
#include <string>
#include <sys/select.h>
#include <vector>

#include "fileOps.h"
#include "stringUtils.h"

#define UPPER_LIMIT 100


namespace advent { namespace y2015 { namespace d15
{
	struct ingredient_t
	{
		std::string name;
		std::vector<int> values;
		int calories;
	};

	ingredient_t parseLine(
			const std::string& source)
	{
		std::vector<std::string> targets { ": ", ", " };
		std::vector<std::string> replacements { " ", " " };

		auto cleaned = utility::string::replace(source, targets, replacements);
		auto split = utility::string::split(cleaned, " ");

		std::string name { split[0] };

		std::vector<int> values;

		for (std::size_t i = 2; i < split.size() - 2; i += 2)
		{
			values.push_back(std::stoi(split[i]));
		}

		int calories = std::stoi(split[split.size() - 1]);

		return { name, values, calories };
	}

	std::tuple<int*, int, int*> loadInput(
			const std::string& inFilename)
	{
		auto source = utility::fileOps::readFileToLines(inFilename);

		int* ingredients = (int*)malloc(4 * 4 * sizeof(int));
		int* calories = (int*)malloc(4 * sizeof(int));

		for (std::size_t i = 0; i < source.size(); i++)
		{
			const auto& line = source[i];

			auto parsed = parseLine(line);

			for (std::size_t j = 0; j < parsed.values.size(); j++)
			{
				ingredients[i * 4 + j] = parsed.values[j];
			}

			calories[i] = parsed.calories;
		}

		return { ingredients, source.size(), calories };
	}

	int evaluateRecipe(
			int* ingredients,
			int* caloriesSource,
			std::size_t numIngredients,
			int* counts,
			int calorieTarget)
	{
		int propValues[4] { 0, 0, 0, 0 };
		int calories = 0;

		for (std::size_t i = 0; i < numIngredients; i++)
		{
			for (std::size_t j = 0; j < 4; j++)
			{
				propValues[j] += ingredients[i * 4 + j] * counts[i];
			}

			calories += caloriesSource[i] * counts[i];
		}

		if (calorieTarget != -1 && calories != calorieTarget)
			return 0;

		auto result = 1;

		for (std::size_t i = 0; i < 4; i++)
		{
			if (propValues[i] < 0)
				result = 0;

			result *= propValues[i];
		}

		return result;
	}

	int findMaxValue(
			int* ingredients,
			int* calories,
			std::size_t numIngredients,
			int calorieTarget)
	{
		int result = std::numeric_limits<int>::min();

		int counts[4];

		for (counts[0] = 0; counts[0] <= UPPER_LIMIT; counts[0]++)
		{
			for (counts[1] = 0; counts[0] + counts[1] <= UPPER_LIMIT; counts[1]++)
			{
				for (counts[2] = 0; counts[0] + counts[1] + counts[2] <= UPPER_LIMIT; counts[2]++)
				{
					for (counts[3] = 0; counts[0] + counts[1] + counts[2] + counts[3] <= UPPER_LIMIT; counts[3]++)
					{
						auto optionResult = evaluateRecipe(ingredients, calories, numIngredients, counts, calorieTarget);

						result = result > optionResult ? result : optionResult;
					}
				}
			}
		}

		return result;
	}


	std::string partOne(
			const std::string& inFilename)
	{
		const auto& [ ingredients, numIngredients, calories ] = loadInput(inFilename);

		auto result = findMaxValue(ingredients, calories, numIngredients, -1);

		return std::to_string(result);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		const auto& [ ingredients, numIngredients, calories ] = loadInput(inFilename);

		auto result = findMaxValue(ingredients, calories, numIngredients, 500);

		return std::to_string(result);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }
