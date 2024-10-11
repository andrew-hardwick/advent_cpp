#ifndef ADVENT_ARGUMENT_PARSING_H
#define ADVENT_ARGUMENT_PARSING_H

#include <argp.h>
#include <string>
#include <tuple>


namespace advent { namespace argumentParsing
{
	error_t parse_opt(
			int key,
			char* arg,
			struct argp_state* state);

	std::tuple<std::string, std::string, std::string, bool> parseArguments(
			int argc,
			char** argv);
} }

#endif
