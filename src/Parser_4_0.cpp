#include <string>
#include <map>

#include "IParser.h"
#include "Parser_4_0.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_4_0::Parser_4_0(cpuid_response const &data) :
    result { },
    moreCaches { false }
{
    parseRAX(data.RAX());

    if (moreCaches)
    {
        parseRBX(data.RBX());
        parseRCX(data.RCX());
        parseRDX(data.RDX());
    }
}

Parser_4_0::~Parser_4_0()
{
}

parse_result_t Parser_4_0::parse() const
{
    return result;
}

void Parser_4_0::parseRAX(size_t value)
{
    bit_extractor extr { value };

    {
        size_t const val = extr.extract(4, 0);

        std::map<size_t, std::string> const map
        {
            { 0, "No more caches" },
            { 1, "Data cache" },
            { 2, "Instruction cache" },
            { 3, "Unified cache" }
        };

        if (auto ct = map.find(val); ct != map.end())
        {
            result.push_back(ct->second);
        }
        else
        {
            result.push_back("Cache type unknown");
        }

        moreCaches = (val != 0);

        if (!moreCaches)
        {
            return;
        }
    }

    {
        ParserString pstr { "Cache level", extr.extract(7, 5) };
        result.push_back(pstr.str());
    }

    result.push_back(extr.extract(8) ? "Self initializing" : "Not self initializing");

    result.push_back(extr.extract(9) ? "Fully associative" : "Not fully associative");

    {
        ParserString pstr
        {
            "Max. number of addressible IDs for logical processors sharing this cache",
            1 + extr.extract(25, 14)
        };
        result.push_back(pstr.str());
    }

    {
        ParserString pstr
        {
            "Max. number of addressible IDs for processor cores in the physical package",
            1 + extr.extract(31, 26)
        };
        result.push_back(pstr.str());
    }
}

void Parser_4_0::parseRBX(size_t value)
{
    bit_extractor extr { value };

    {
        ParserString pstr { "System coherency line size", 1 + extr.extract(11, 0) };
        result.push_back(pstr.str());
    }

    {
        ParserString pstr { "Physical line partitions", 1 + extr.extract(21, 12) };
        result.push_back(pstr.str());
    }

    {
        ParserString pstr { "Ways of associativity", 1 + extr.extract(31, 22) };
        result.push_back(pstr.str());
    }
}

void Parser_4_0::parseRCX(size_t value)
{
    ParserString pstr { "Number of sets", (value + 1) };
    result.push_back(pstr.str());
}

void Parser_4_0::parseRDX(size_t value)
{
    bit_extractor extr { value };

    result.push_back(extr.extract(0) ?
            "WBINVD/INVD is not guaranteed to act upon lower level caches of non-originating threads sharing this cache" :
            "WBINVD/INVD from threads sharing this cache acts upon lower level caches for threads sharing this cache.");

    result.push_back(extr.extract(1) ?
            "Cache is inclusive of lower cache levels" :
            "Cache is not inclusive of lower cache levels");

    result.push_back(extr.extract(2) ?
            "A complex function is used to index the cache, potentially using all address bits" :
            "Direct mapped cache");
}
