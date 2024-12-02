#include "02.h"

#include <algorithm>

#include "fileOps.h"
#include "stringUtils.h"


namespace advent { namespace y2024 { namespace d02
{
	std::vector<int> parseLine(
			const std::string& line)
	{
		return utility::string::parseToIntArray(line, " ");
	}

	std::vector<std::vector<int>> loadInput(
			const std::string& inFilename)
	{
		auto source = utility::fileOps::readFileToLines(inFilename);

		std::vector<std::vector<int>> result(source.size());

		std::transform(source.cbegin(), source.cend(), result.begin(), parseLine);

		return result;
	}

	uint evaluateReportPartOne(
			const std::vector<int>& report)
	{
		if (report.size() < 2)
			return 0;

		if (report[0] == report[1])
			return 0;

		auto direction = (report[0] - report[1]) / (int)(std::abs(report[0] - report[1]));

		for (std::size_t i = 0; i < report.size() - 1; i++)
		{
			auto first = report[i];
			auto second = report[i + 1];

			if (first == second)
				return 0;

			auto delta = first - second;
			auto deltaMag = (int)std::abs(delta);

			if (deltaMag < 1 || deltaMag > 3)
				return 0;

			if (delta / deltaMag != direction)
				return 0;
		}

		return 1;
	}

	uint evaluateReportPartTwo(
			const std::vector<int>& report)
	{
		auto unperturbed = evaluateReportPartOne(report);

		if (unperturbed == 1)
			return 1;

		for (std::size_t i = 0; i < report.size(); i++)
		{
			std::vector<int> partial;

			for (std::size_t j = 0; j < report.size(); j++)
			{
				if (i != j)
					partial.push_back(report.at(j));
			}

			auto perturbed = evaluateReportPartOne(partial);

			if (perturbed == 1)
				return 1;
		}

		return 0;
	}

	std::string partOne(
			const std::string& inFilename)
	{
		auto data = loadInput(inFilename);

		uint result = 0;

		for (const auto& report : data)
			result += evaluateReportPartOne(report);

		return std::to_string(result);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		auto data = loadInput(inFilename);

		std::size_t result = 0;

		for (const auto& report : data)
			result += evaluateReportPartTwo(report);

		return std::to_string(result);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }
