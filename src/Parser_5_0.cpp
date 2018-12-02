#include <string>
#include <map>
#include <utility>

#include "IParser.h"
#include "Parser_5_0.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_5_0::Parser_5_0(cpuid_response const &data) :
    result { }
{
    parseRAX(data.RAX());
    parseRBX(data.RBX());
    parseRCX(data.RCX());
    parseRDX(data.RDX());
}

Parser_5_0::~Parser_5_0()
{
}

parse_result_t Parser_5_0::parse()
{
    return result;
}

void Parser_5_0::parseRAX(size_t value)
{
    bit_extractor extr { value };
    ParserString pstr { "Smallest monitor-line size in bytes", extr.extract(15, 0) };
    result.push_back(pstr.str());
}

void Parser_5_0::parseRBX(size_t value)
{
    bit_extractor extr { value };
    ParserString pstr { "Largest monitor-line size in bytes", extr.extract(15, 0) };
    result.push_back(pstr.str());
}

void Parser_5_0::parseRCX(size_t value)
{
    bit_extractor extr { value };

    if (extr.extract(0))
    {
        result.push_back("Enumeration of Monitor-Mwait extensions supported");
    }

    if (extr.extract(1))
    {
        result.push_back("Treating interrupts as break-event for MWAIT, even when interrupts disabled, supported");
    }
}

void Parser_5_0::parseRDX(size_t value)
{
    bit_extractor extr { value };

    std::map<std::string, std::pair<size_t, size_t>> const table
    {
        { "Number of C0* sub C-states supported using MWAIT", { 3, 0 } },
        { "Number of C1* sub C-states supported using MWAIT", { 7, 4 } },
        { "Number of C2* sub C-states supported using MWAIT", { 11, 8 } },
        { "Number of C3* sub C-states supported using MWAIT", { 15, 12 } },
        { "Number of C4* sub C-states supported using MWAIT", { 19, 16 } },
        { "Number of C5* sub C-states supported using MWAIT", { 23, 20 } },
        { "Number of C6* sub C-states supported using MWAIT", { 27, 24 } },
        { "Number of C7* sub C-states supported using MWAIT", { 31, 28 } }
    };

    for (auto &t: table)
    {
        ParserString pstr { t.first, extr.extract(t.second) };
        result.push_back(pstr.str());
    }
}
