#include "08.h"

#include "fileOps.h"
#include <string>


namespace advent { namespace y2015 { namespace d08
{
	std::string decodeString(
			std::string working)
	{
		// removing the enclosing quotes
		working = working.substr(1, working.size() - 2);

		std::string result;

		for (std::size_t i = 0; i < working.size(); i++)
		{
			if (working.at(i) == '\\')
			{
				if (working.at(i + 1) == 'x')
				{
					// hex
					// we don't actually have to decode the character
					result += '%';
					
					i += 3;
				}
				else
				{
					// single escaped character
					result += working.at(i + 1);

					i++;
				}
			}
			else
			{
				result += working.at(i);
			}
		}

		return result;
	}

	std::string encodeString(
			const std::string& source)
	{
		std::string result = "\"";

		for (const auto& c : source)
		{
			if (c == '"' || c == '\\')
			{
				result += '\\';
			}

			result += c;
		}

		result += "\"";

		return result;
	}

	std::string partOne(
			const std::string& inFilename)
	{
		auto lines = utility::fileOps::readFileToLines(inFilename);

		int result = 0;

		for (const auto& line : lines)
		{
			result += line.size() - decodeString(line).size();
		}
		
		return std::to_string(result);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		auto lines = utility::fileOps::readFileToLines(inFilename);

		int result = 0;

		for (const auto& line : lines)
		{
			result += encodeString(line).size() - line.size();
		}
		
		return std::to_string(result);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }

