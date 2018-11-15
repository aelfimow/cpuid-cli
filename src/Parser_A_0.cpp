#include <string>
#include <map>
#include <utility>

#include "IParser.h"
#include "Parser_A_0.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_A_0::Parser_A_0(cpuid_response const &data) :
    result { }
{
    parseRAX(data.RAX());
    parseRBX(data.RBX());
    parseRCX(data.RCX());
    parseRDX(data.RDX());
}

Parser_A_0::~Parser_A_0()
{
}

parse_result_t Parser_A_0::parse() const
{
    return result;
}

void Parser_A_0::parseRAX(size_t value)
{
    bit_extractor extr { value };

    std::map<std::string, std::pair<size_t, size_t>> const table
    {
        { "Version ID of architectural performance monitoring: ", { 7, 0 } },
        { "Number of general-purpose performance monitoring counter per logical processor: ", { 15, 8 } },
        { "Bit width of general-purpose, performance monitoring counter: ", { 23, 16 } },
        { "Length of EBX bit vector to enumerate architectural performance monitoring events: ", { 31, 24 } }
    };

    for (auto &t: table)
    {
        ParserString pstr { t.first, extr.extract(t.second) };

        result.push_back(pstr.str());
    }
}

void Parser_A_0::parseRBX(size_t value)
{
    bit_extractor extr { value };

    std::map<size_t, std::string> const table
    {
        { 0, "Core cycle event" },
        { 1, "Instruction retired event" },
        { 2, "Reference cycles event" },
        { 3, "Last-level cache reference event" },
        { 4, "Last-level cache misses event" },
        { 5, "Branch instruction retired event" },
        { 6, "Branch mispredict retired event" }
    };

    for (auto &t: table)
    {
        std::string str { t.second };

        str.append(extr.extract(t.first) ? " not available" : " available");

        result.push_back(str);
    }
}

void Parser_A_0::parseRCX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_A_0::parseRDX(size_t value)
{
    bit_extractor extr { value };

    {
        ParserString pstr
        {
            "Number of fixed-function performance counters: ",
            extr.extract(4, 0)
        };

        result.push_back(pstr.str());
    }

    {
        ParserString pstr
        {
            "Bit width of fixed-function performance counters: ",
            extr.extract(12, 5)
        };

        result.push_back(pstr.str());
    }
}
