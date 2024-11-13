#include "11.h"

#include <algorithm>
#include <ctime>

#include "fileOps.h"


namespace advent { namespace y2015 { namespace d11
{
	std::vector<std::size_t> decompose(
			const std::string& password)
	{
		std::vector<std::size_t> result;

		for (const auto& c : password)
		{
			result.push_back(c - 'a');
		}

		return result;
	}

	std::string reconstitute(
			const std::vector<std::size_t>& password)
	{
		std::string result;

		for (const auto& c : password)
		{
			result += ((char)(c + 'a'));
		}

		return result;
	}

	void step(
			std::vector<std::size_t>& password)
	{
		auto lastIndex = password.size() - 1;

		password[lastIndex]++;

		auto cursorIndex = lastIndex;

		while (password[cursorIndex] > 25 && cursorIndex != 0)
		{
			password[cursorIndex] = 0;
			password[cursorIndex - 1]++;
			cursorIndex--;
		}
	}

	bool ascendingChain(
			const std::vector<std::size_t>& password)
	{
		for (std::size_t i = 0; i < password.size() - 2; i++)
		{
			auto c0 = password.at(i);
			auto c1 = password.at(i + 1);
			auto c2 = password.at(i + 2);

			if (c2 - c1 == 1 && c1 - c0 == 1)
				return true;
		}

		return false;
	}

	bool noNaughtyChars(
			const std::vector<std::size_t>& password)
	{
		std::vector<std::size_t> naughtyChars { 11, 8, 14 };

		for (const auto& c : naughtyChars)
		{
			if (std::find(password.begin(), password.end(), c) != password.end())
				return false;
		}

		return true;
	}

	bool twoPairs(
			const std::vector<std::size_t>& password)
	{
		for (std::size_t i = 0; i < password.size() - 3; i++)
		{
			if (password.at(i) == password.at(i + 1))
			{
				for (std::size_t j = i + 2; j < password.size() - 1; j++)
				{
					if (password.at(j) == password.at(j + 1))
							return true;
				}
			}
		}

		return false;
	}

	bool notAcceptable(
			const std::vector<std::size_t>& password)
	{
		auto chain = ascendingChain(password);
		auto naughty = noNaughtyChars(password);
		auto pairs = twoPairs(password);

		return !chain || !naughty || !pairs;
	}

	std::string nextPassword(
			const std::string& source)
	{
		auto password = decompose(source);

		do
		{
			step(password);
		} while (notAcceptable(password));

		auto result = reconstitute(password);

		return result;
	}

	std::string partOne(
			const std::string& inFilename)
	{
		auto source = utility::fileOps::readFileToLines(inFilename)[0];

		return nextPassword(source);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		auto source = utility::fileOps::readFileToLines(inFilename)[0];

		auto next = nextPassword(source);

		return nextPassword(next);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }

