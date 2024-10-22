#include "lib2015.h"

#include "01.h"
#include "02.h"
#include "03.h"
#include "04.h"
#include "05.h"
#include "06.h"
#include "07.h"
#include "08.h"
#include "09.h"
#include "10.h"

#include <stdexcept>


namespace advent { namespace y2015
{
	std::pair<adventFunctor, adventFunctor> getDay(
			const std::string& day)
	{
		if ("1" == day || "01" == day)
			return d01::getParts();
		if ("2" == day || "02" == day)
			return d02::getParts();
		if ("3" == day || "03" == day)
			return d03::getParts();
		if ("4" == day || "04" == day)
			return d04::getParts();
		if ("5" == day || "05" == day)
			return d05::getParts();
		if ("6" == day || "06" == day)
			return d06::getParts();
		if ("7" == day || "07" == day)
			return d07::getParts();
		if ("8" == day || "08" == day)
			return d08::getParts();
		if ("9" == day || "09" == day)
			return d09::getParts();
		if ("10" == day)
			return d10::getParts();

		throw std::invalid_argument("Encountered unparseable day");
	}
} }
