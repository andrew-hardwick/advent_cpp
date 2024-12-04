#include "fileOps.h"

#include <fstream>
#include <string>
#include <sstream>
#include <vector>


namespace advent { namespace utility { namespace fileOps
{
	std::string readFileRaw(
			const std::string& inFilename)
	{
		std::ifstream inf(inFilename);

		std::stringstream strStream;

		strStream << inf.rdbuf();

		std::string result = strStream.str();

		return result;
	}

	std::vector<char> readFileToChars(
			const std::string& inFilename)
	{
		std::vector<char> result;

		auto lines = readFileToLines(inFilename);

		for (const auto& line : lines)
		{
			result.insert(result.end(), line.begin(), line.end());
		}

		return result;
	}

	std::vector<std::string> readFileToLines(
			const std::string& inFilename)
	{
		std::vector<std::string> result;

		std::ifstream inf(inFilename);

		std::string line;

		while(!inf.eof())
		{
			if (std::getline(inf, line, '\n'))
			{	
				result.push_back(line);
			}
		}

		return result;
	}

	nlohmann::json readFileToJson(
			const std::string& inFilename)
	{
		nlohmann::json result;

		std::ifstream inf(inFilename);

		inf >> result;

		return result;
	}
} } }

