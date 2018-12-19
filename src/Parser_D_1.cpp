#include <string>
#include <map>
#include <bitset>

#include "IParser.h"
#include "Parser_D_1.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_D_1::Parser_D_1(cpuid_response const &data) :
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_response_ok { 1 == data.RCX_Command() },
    m_result { }
{
}

Parser_D_1::~Parser_D_1()
{
}

parse_result_t Parser_D_1::parse()
{
    m_result.clear();

    if (m_response_ok)
    {
        parseRAX(m_RAX);
        parseRBX(m_RBX);
        parseRCX(m_RCX);
        parseRDX(m_RDX);
    }

    return m_result;
}

void Parser_D_1::parseRAX(size_t value)
{
    bit_extractor extr { value };

    std::map<size_t, std::string> const table
    {
        { 0, "XSAVEOPT is available" },
        { 1, "Supports XSAVEC and the compacted form of XRSTOR" },
        { 2, "Supports XGETBV with ECX = 1" },
        { 3, "Supports XSAVES/XRSTORS and IA32_XSS" }
    };

    for (auto &t: table)
    {
        if (extr.extract(t.first))
        {
            m_result.push_back(t.second);
        }
    }
}

void Parser_D_1::parseRBX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "The size in bytes of the XSAVE area containing all states enabled by XCRO | IA32_XSS",
        extr.extract(31, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_D_1::parseRCX(size_t value)
{
    std::bitset<32> bin_value { value };

    ParserString pstr
    {
        "Lower 32 bits of the IA32_XSS MSR",
        bin_value.to_string()
    };

    m_result.push_back(pstr.str());
}

void Parser_D_1::parseRDX(size_t value)
{
    std::bitset<32> bin_value { value };

    ParserString pstr
    {
        "Upper 32 bits of the IA32_XSS MSR",
        bin_value.to_string()
    };

    m_result.push_back(pstr.str());
}
