#include "14.h"

#include "fileOps.h"
#include "stringUtils.h"

#include <algorithm>
#include <string>
#include <vector>

#include <iostream>

namespace advent { namespace y2015 { namespace d14
{
	struct reindeerStats_t
	{
		std::string name;
		int speed;
		int activeTime;
		int restTime;
		bool currentState;
		int currentStateTime;
		int currentDistance;
		int currentScore;
	};

	reindeerStats_t parseLine(
			const std::string& line)
	{
		std::vector<std::string> targets { " can fly ", " km/s for ", " seconds, but then must rest for ", " seconds." };
		std::vector<std::string> replacements { " ", " ", " ", "" };

		auto cleaned = utility::string::replace(line, targets, replacements);

		auto split = utility::string::split(cleaned, " ");

		return { split[0], std::stoi(split[1]), std::stoi(split[2]), std::stoi(split[3]), true, 1, 0, 0 };
	}

	std::vector<reindeerStats_t> loadInput(
			const std::string& inFilename)
	{
		auto source = utility::fileOps::readFileToLines(inFilename);

		std::vector<reindeerStats_t> result;

		for (const auto& line : source)
		{
			result.push_back(parseLine(line));
		}

		return result;
	}

	void step(
			std::vector<reindeerStats_t>& reindeers)
	{
		for (auto& reindeer : reindeers)
		{
			if (reindeer.currentState && reindeer.currentStateTime > reindeer.activeTime)
			{
				reindeer.currentState = false;
				reindeer.currentStateTime = 1;
			}
			else if (!reindeer.currentState && reindeer.currentStateTime > reindeer.restTime)
			{
				reindeer.currentState = true;
				reindeer.currentStateTime = 1;
			}

			if (reindeer.currentState)
			{
				reindeer.currentDistance += reindeer.speed;
			}

			reindeer.currentStateTime++;
		}

		int best = 0;

		for (const auto& reindeer : reindeers)
		{
			best = std::max(best, reindeer.currentDistance);
		}

		for (auto& reindeer : reindeers)
		{
			if (reindeer.currentDistance == best)
			{
				reindeer.currentScore++;
			}
		}
	}

	std::string partOne(
			const std::string& inFilename)
	{
		auto reindeer = loadInput(inFilename);

		for (std::size_t i = 0; i < 2503; i++)
		{
			step(reindeer);
		}

		int best = 0;

		for (const auto& r : reindeer)
		{
			best = std::max(best, r.currentDistance);
		}

		return std::to_string(best);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		auto reindeer = loadInput(inFilename);

		for (std::size_t i = 0; i < 2503; i++)
		{
			step(reindeer);
		}

		int best = 0;

		for (const auto& r : reindeer)
		{
			best = std::max(best, r.currentScore);
		}

		return std::to_string(best);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }

