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

    size_t const selfInit = extr.extract(8, 8);
    result.push_back(selfInit ? "Self initializing" : "Not self initializing");

    size_t const fullyAssoc = extr.extract(9, 9);
    result.push_back(fullyAssoc ? "Fully associative" : "Not fully associative");

    {
        size_t const val = extr.extract(25, 14);
        std::stringstream ss;
        ss << "Max. number of addressible IDs for logical processors sharing this cache: ";
        ss << val;
        result.push_back(ss.str());
    }
    {
        size_t const val = extr.extract(31, 26);
        std::stringstream ss;
        ss << "Max. number of addressible IDs for processor cores in the physical package: ";
        ss << val;
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
        ss << val;
        result.push_back(ss.str());
    }
    {
        size_t const val = extr.extract(21, 12);
        std::stringstream ss;
        ss << "Physical line partitions: ";
        ss << val;
        result.push_back(ss.str());
    }
    {
        size_t const val = extr.extract(31, 22);
        std::stringstream ss;
        ss << "Ways of associativity: ";
        ss << val;
        result.push_back(ss.str());
    }
}

void Parser_4_0::parseRCX(size_t value)
{
    std::stringstream ss;
    ss << "Number of sets: ";
    ss << value;
    result.push_back(ss.str());
}

void Parser_4_0::parseRDX(size_t value)
{
}
