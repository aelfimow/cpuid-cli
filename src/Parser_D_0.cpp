#include <string>
#include <map>
#include <bitset>

#include "IParser.h"
#include "Parser_D_0.h"
#include "Parser_D_1.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_D_0::Parser_D_0(cpuid_response const &data) :
    m_result { },
    m_next { nullptr }
{
    bool response_ok = (0 == data.RCX_Command());

    if (response_ok)
    {
        parseRAX(data.RAX());
        parseRBX(data.RBX());
        parseRCX(data.RCX());
        parseRDX(data.RDX());
    }
    else
    {
        m_next = new Parser_D_1 { data };
    }
}

Parser_D_0::~Parser_D_0()
{
    delete m_next;
}

parse_result_t Parser_D_0::parse() const
{
    if (m_next != nullptr)
    {
        return m_next->parse();
    }

    return m_result;
}

void Parser_D_0::parseRAX(size_t value)
{
    bit_extractor extr { value };

    std::map<std::pair<size_t, size_t>, std::string> const table
    {
        { { 0, 0 }, "x87 state" },
        { { 1, 1 }, "SSE state" },
        { { 2, 2 }, "AVX state" },
        { { 4, 3 }, "MPX state" },
        { { 7, 5 }, "AVX-512 state" },
        { { 8, 8 }, "Used for IA32_XSS" },
        { { 9, 9 }, "PKRU state" }
    };

    for (auto &t: table)
    {
        ParserString pstr { t.second, extr.extract(t.first) };
        m_result.push_back(pstr.str());
    }
}

void Parser_D_0::parseRBX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Maximum size required by enabled features in XCR0",
        extr.extract(31, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_D_0::parseRCX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Maximum size of the XSAVE/XRSTOR save area required by all supported features",
        extr.extract(31, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_D_0::parseRDX(size_t value)
{
    std::bitset<32> bin_value { value };

    ParserString pstr
    {
        "Upper 32 bits of XCR0",
        bin_value.to_string()
    };

    m_result.push_back(pstr.str());
}
