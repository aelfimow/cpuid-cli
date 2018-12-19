#include <string>
#include <map>

#include "IParser.h"
#include "Parser_B_0.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_B_0::Parser_B_0(cpuid_response const &data) :
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_result { },
    sub_leaf_valid { false },
    shift_value { 0 }
{
}

Parser_B_0::~Parser_B_0()
{
}

parse_result_t Parser_B_0::parse()
{
    m_result.clear();
    sub_leaf_valid = false;
    shift_value = 0;

    parseRCX(m_RCX);

    if (sub_leaf_valid)
    {
        parseRAX(m_RAX);
        parseRBX(m_RBX);
        parseRDX(m_RDX);
    }

    return m_result;
}

void Parser_B_0::parseRAX(size_t value)
{
    bit_extractor extr { value };

    shift_value = extr.extract(4, 0);
}

void Parser_B_0::parseRBX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr { "Number of logical processors at this level type", extr.extract(15, 0) };

    m_result.push_back(pstr.str());
}

void Parser_B_0::parseRCX(size_t value)
{
    bit_extractor extr { value };

    size_t const level_type = extr.extract(15, 8);

    sub_leaf_valid = (0 != level_type);

    if (sub_leaf_valid)
    {
        std::map<size_t, std::string> const table
        {
            { 1, "SMT" },
            { 2, "Core" }
        };

        if (auto it = table.find(level_type); it != table.end())
        {
            m_result.push_back("Level type is " + it->second);
        }
    }
}

void Parser_B_0::parseRDX(size_t value)
{
    bit_extractor extr { value };

    size_t x2APIC_ID = extr.extract(31, 0);

    x2APIC_ID <<= shift_value;

    ParserString pstr { "x2APIC ID", x2APIC_ID };
}
