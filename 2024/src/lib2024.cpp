#include "lib2024.h"

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
#include "11.h"
#include "12.h"
#include "13.h"
#include "14.h"
#include "15.h"
#include "16.h"
#include "17.h"
#include "18.h"
#include "19.h"
#include "20.h"
#include "21.h"
#include "22.h"
#include "23.h"
#include "24.h"
#include "25.h"

#include <stdexcept>

namespace advent { namespace y2024
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
		if ("10" == day || "10" == day)
			return d10::getParts();
		if ("11" == day)
			return d11::getParts();
		if ("12" == day)
			return d12::getParts();
		if ("13" == day)
			return d13::getParts();
		if ("14" == day)
			return d14::getParts();
		if ("15" == day)
			return d15::getParts();
		if ("16" == day)
			return d16::getParts();
		if ("17" == day)
			return d17::getParts();
		if ("18" == day)
			return d18::getParts();
		if ("19" == day)
			return d19::getParts();
		if ("20" == day)
			return d20::getParts();
		if ("21" == day)
			return d21::getParts();
		if ("22" == day)
			return d22::getParts();
		if ("23" == day)
			return d23::getParts();
		if ("24" == day)
			return d24::getParts();
		if ("25" == day)
			return d25::getParts();

		throw std::invalid_argument("Encountered unparseable day");
	}
} }
