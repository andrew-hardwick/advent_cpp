#ifndef ADVENT_FILE_OPS_H
#define ADVENT_FILE_OPS_H

#include <string>
#include <vector>

#include "nlohmann/json.hpp"


namespace advent { namespace utility { namespace fileOps
{
	std::string readFileRaw(
			const std::string& inFilename);

	std::vector<char> readFileToChars(
			const std::string& inFilename);

	std::vector<std::string> readFileToLines(
			const std::string& inFilename);

	nlohmann::json readFileToJson(
			const std::string& inFilename);
} } }

#endif
