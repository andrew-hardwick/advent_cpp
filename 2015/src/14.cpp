#include "14.h"

#include "fileOps.h"
#include "stringUtils.h"

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

		return { split[0], std::stoi(split[1]), std::stoi(split[2]), std::stoi(split[3]), true, 0, 0, 0 };
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
				reindeer.activeTime = 0;
			}
			else if (!reindeer.currentState && reindeer.currentStateTime > reindeer.restTime)
			{
				reindeer.currentState = true;
				reindeer.activeTime = 0;
			}

			if (reindeer.currentState)
			{
				reindeer.currentDistance += reindeer.speed;
			}

			reindeer.activeTime++;
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

		for (const auto& r : reindeer)
		{
			std::cout << r.name << r.currentDistance << "\n";
		}

		return "nonimpl";
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

