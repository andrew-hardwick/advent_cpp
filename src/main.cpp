#include "argumentParsing.h"

#include "evaluator.h"


int main(
		int argc,
		char** argv)
{
	auto [ year, day, inFile, verbose ] = advent::argumentParsing::parseArguments(argc, argv);

	advent::evaluate(year, day, inFile, verbose);
}
