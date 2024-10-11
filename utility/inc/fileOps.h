#ifndef ADVENT_FILE_OPS_H
#define ADVENT_FILE_OPS_H

#include <string>
#include <vector>


namespace advent { namespace utility { namespace fileOps
{
	std::vector<char> readFileToChars(
			const std::string& inFilename);

	std::vector<std::string> readFileToLines(
			const std::string& inFilename);
} } }

#endif
