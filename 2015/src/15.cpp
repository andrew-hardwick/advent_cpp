#include "15.h"

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "fileOps.h"
#include "stringUtils.h"
#include "vectorMath.h"


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

	std::vector<ingredient_t> loadInput(
			const std::string& inFilename)
	{
		auto source = utility::fileOps::readFileToLines(inFilename);

		std::vector<ingredient_t> result;

		for (const auto& line : source)
		{
			result.push_back(parseLine(line));
		}

		return result;
	}

	std::tuple<int, int> evaluateRecipe(
			const std::vector<ingredient_t>& ingredients,
			const std::vector<int> amounts)
	{
		std::vector<int> ingredientValues;
		int calories = 0;

		for (std::size_t i = 0; i < ingredients.at(0).values.size(); i++)
		{
			ingredientValues.push_back(0);
		}

		for (std::size_t i = 0; i < amounts.size(); i++)
		{
			auto ingredientValue = utility::vectorMath::multiplyByScalar(ingredients.at(i).values, amounts.at(i));

			for (std::size_t j = 0; j < ingredientValue.size(); j++)
			{
				ingredientValues[j] += ingredientValue[j];
			}

			calories += amounts[i] * ingredients[i].calories;
		}

		return { utility::vectorMath::sum(ingredientValues), calories };
	}

	std::vector<int> getBalancedAmounts(
			std::size_t count,
			int total)
	{
		std::vector<int> result;

		int portion = total / count;
		int remainder = total % count;

		for (std::size_t i = 0; i < count; i++)
		{
			result.push_back(portion);
		}

		result.at(0) += remainder;

		return result;
	}

	void optimize(
			std::vector<int>& amounts,
			const std::vector<ingredient_t>& ingredients,
			std::function<bool(int)> isRecipeAcceptable,
			float momentum,
			std::function<int(int)> reduceMomentum)
	{
	}

	std::string partOne(
			const std::string& inFilename)
	{
		auto ingredients = loadInput(inFilename);

		auto amounts = getBalancedAmounts(ingredients.size(), 100);

		auto isRecipeAcceptable = [](int c){return true;};
		auto reduceMomentum = [](float momentum)
		{
			return momentum * 0.99;
		};

		optimize(amounts, ingredients, isRecipeAcceptable, 15, reduceMomentum);

		auto [ score, calories ] = evaluateRecipe(ingredients, amounts);

		return std::to_string(score);
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
