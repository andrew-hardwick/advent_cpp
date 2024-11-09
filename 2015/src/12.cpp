#include "12.h"

#include <cctype>
#include <string>

#include "fileOps.h"
#include "nlohmann/json.hpp"


namespace advent { namespace y2015 { namespace d12
{
	long long sumChildrenArray(
			const nlohmann::json& source,
			bool applyFilter);

	long long sumChildrenObject(
			const nlohmann::json& source,
			bool applyFilter);

	long long sumChildrenArray(
			const nlohmann::json& source,
			bool applyFilter)
	{
		long long result = 0;

		for (const auto& entry : source)
		{
			if (entry.is_number_integer())
			{
				result += (long long) entry;
			}
			else if (entry.is_array())
			{
				result += sumChildrenArray(entry, applyFilter);
			}
			else if (entry.is_object())
			{
				result += sumChildrenObject(entry, applyFilter);
			}
		}

		return result;
	}

	long long sumChildrenObject(
			const nlohmann::json& source,
			bool applyFilter)
	{
		long long result = 0;

		for (const auto& item : source.items())
		{
			auto entry = item.value();

			if (applyFilter && entry == "red")
			{
				return 0;
			}

			if (entry.is_number_integer())
			{
				result += (long long) entry;
			}
			else if (entry.is_array())
			{
				result += sumChildrenArray(entry, applyFilter);
			}
			else if (entry.is_object())
			{
				result += sumChildrenObject(entry, applyFilter);
			}
		}

		return result;
	}

	long long sumChildren(
			const nlohmann::json& source,
			bool applyFilter)
	{
		if (source.is_array())
		{
			return sumChildrenArray(source, applyFilter);
		}
		else if (source.is_object())
		{
			return sumChildrenObject(source, applyFilter);
		}

		return source;
	}

	std::string partOne(
			const std::string& inFilename)
	{
		auto source = utility::fileOps::readFileToJson(inFilename);

		return std::to_string(sumChildren(source, false));
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		auto source = utility::fileOps::readFileToJson(inFilename);

		return std::to_string(sumChildren(source, true));
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }

