#include "argumentParsing.h"
#include <tuple>


namespace advent { namespace argumentParsing
{
	const char* argp_program_version = "advent 0.0.1";
	const char* argp_program_bug_address = "drew.hardwick@gmail.com";

	struct arguments
	{
		char* args[3];
		int verbose;
	};

	static struct argp_option options[] =
	{
		{"verbose", 'v', 0, 0, "Produce verbose output"},
		{0}
	};

	error_t parse_opt(
			int key,
			char* arg,
			struct argp_state* state)
	{
		struct arguments* arguments = (struct arguments*) state->input;

		switch (key)
		{
			case 'v':
				arguments->verbose = 1;
				break;
			case ARGP_KEY_ARG:
				if (state->arg_num >= 3)
				{
					argp_usage(state);
				}
				arguments->args[state->arg_num] = arg;
				break;
			case ARGP_KEY_END:
				if (state->arg_num < 3)
				{
					argp_usage(state);
				}
				break;
			default:
				return ARGP_ERR_UNKNOWN;
		}

		return 0;
	}

	static char args_doc[] = "Year Date InputFilename";

	static char doc[] = "advent - A program to execute advent of code problems";

	static struct argp argp = {options, parse_opt, args_doc, doc};

	std::tuple<std::string, std::string, std::string, bool> parseArguments(
			int argc,
			char** argv)
	{
		struct arguments arguments;

		argp_parse(&argp, argc, argv, 0, 0, &arguments);

		std::string year(arguments.args[0]);
		std::string day(arguments.args[1]);
		std::string inFilename(arguments.args[2]);

		bool verbose = arguments.verbose == 1;
		
		std::string outfile;

		return std::make_tuple(year, day, inFilename, verbose);
	}
} }
