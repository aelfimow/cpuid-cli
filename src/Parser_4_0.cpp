#include <sstream>
#include <map>

#include "IParser.h"
#include "Parser_4_0.h"
#include "bit_extractor.h"
#include "cpuid_response.h"


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
        size_t const val = extr.extract(7, 5);

        std::stringstream ss;
        ss << "Cache level: " << val;
        result.push_back(ss.str());
    }

    result.push_back(extr.extract(8) ? "Self initializing" : "Not self initializing");

    result.push_back(extr.extract(9) ? "Fully associative" : "Not fully associative");

    {
        size_t const val = extr.extract(25, 14);
        std::stringstream ss;
        ss << "Max. number of addressible IDs for logical processors sharing this cache: ";
        ss << (val + 1);
        result.push_back(ss.str());
    }
    {
        size_t const val = extr.extract(31, 26);
        std::stringstream ss;
        ss << "Max. number of addressible IDs for processor cores in the physical package: ";
        ss << (val + 1);
        result.push_back(ss.str());
    }
}

void Parser_4_0::parseRBX(size_t value)
{
    bit_extractor extr { value };

    {
        size_t const val = extr.extract(11, 0);
        std::stringstream ss;
        ss << "System coherency line size: ";
        ss << (val + 1);
        result.push_back(ss.str());
    }
    {
        size_t const val = extr.extract(21, 12);
        std::stringstream ss;
        ss << "Physical line partitions: ";
        ss << (val + 1);
        result.push_back(ss.str());
    }
    {
        size_t const val = extr.extract(31, 22);
        std::stringstream ss;
        ss << "Ways of associativity: ";
        ss << (val + 1);
        result.push_back(ss.str());
    }
}

void Parser_4_0::parseRCX(size_t value)
{
    std::stringstream ss;
    ss << "Number of sets: ";
    ss << (value + 1);
    result.push_back(ss.str());
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
