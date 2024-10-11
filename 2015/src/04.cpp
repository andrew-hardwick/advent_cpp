#include "04.h"

#include <limits>

#include "fileOps.h"
#include "stringUtils.h"

#include <openssl/evp.h>


namespace advent { namespace y2015 { namespace d04
{
	std::string md5(
			const std::string& source)
	{
		EVP_MD_CTX* context = EVP_MD_CTX_new();
		const EVP_MD* md = EVP_md5();
		unsigned char md_value[EVP_MAX_MD_SIZE];
		unsigned int md_len;
		std::string result;

		EVP_DigestInit_ex2(context, md, NULL);
		EVP_DigestUpdate(context, source.c_str(), source.size());
		EVP_DigestFinal_ex(context, md_value, &md_len);
		EVP_MD_CTX_free(context);

		result.resize(md_len * 2);
		
		for (std::size_t i = 0; i < md_len; i++)
		{
			std::sprintf(&result[i * 2], "%02x", md_value[i]);
		}

		return result;
	}

	std::string execute(
			const std::string& inFilename,
			std::size_t count)
	{
		auto source = utility::fileOps::readFileToLines(inFilename)[0];
		
		for (std::size_t i = 0; i < std::numeric_limits<std::size_t>::max(); i++)
		{
			auto iStr = std::to_string(i);

			auto hashSource = source + iStr;

			auto hash = md5(hashSource);

			if (utility::string::leadCharMatches(hash, '0', count))
			{
				return iStr;
			}
		}

		std::string result = "Unable to find AdventCoin";

		return result;
	}

	std::string partOne(
			const std::string& inFilename)
	{
		return execute(inFilename, 5);
	}

	std::string partTwo(
			const std::string& inFilename)
	{
		return execute(inFilename, 6);
	}

	std::pair<adventFunctor, adventFunctor> getParts()
	{
		return { partOne, partTwo };
	}
} } }
