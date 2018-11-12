#include <map>

#include "IParser.h"
#include "Parser_4_0.h"
#include "bit_extractor.h"
#include "cpuid_response.h"


Parser_4_0::Parser_4_0(cpuid_response const &data) :
    result { }
{
    bit_extractor extr { data.RAX() };

    {
        size_t const cacheType = extr.extract(4, 0);

        std::map<size_t, std::string> const map
        {
            { 0, "No more caches" },
            { 1, "Data cache" },
            { 2, "Instruction cache" },
            { 3, "Unified cache" }
        };

        if (auto ct = map.find(cacheType); ct != map.end())
        {
            result.push_back(ct->second);
        }
        else
        {
            result.push_back("Cache type unknown");
        }
    }
}

Parser_4_0::~Parser_4_0()
{
}

parse_result_t Parser_4_0::parse() const
{
    return result;
}
