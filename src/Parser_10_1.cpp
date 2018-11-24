#include "IParser.h"
#include "Parser_10_1.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_10_1::Parser_10_1(cpuid_response const &data) :
    m_result { },
    m_next { nullptr }
{
    bool response_ok = (1 == data.RCX_Command());

    if (response_ok)
    {
        parseRAX(data.RAX());
        parseRBX(data.RBX());
        parseRCX(data.RCX());
        parseRDX(data.RDX());
    }
}

Parser_10_1::~Parser_10_1()
{
    delete m_next;
}

parse_result_t Parser_10_1::parse() const
{
    if (m_next != nullptr)
    {
        return m_next->parse();
    }

    return m_result;
}

void Parser_10_1::parseRAX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Length of the capacity bit mask",
        1 + extr.extract(4, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_10_1::parseRBX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Bit-granular map of isolation/contention of allocation units",
        extr.extract(31, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_10_1::parseRCX(size_t value)
{
    bit_extractor extr { value };

    if (extr.extract(2))
    {
        m_result.push_back("Code and Data Prioritization Technology supported");
    }
}

void Parser_10_1::parseRDX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Highest COS number supported for ResID 1",
        extr.extract(15, 0)
    };

    m_result.push_back(pstr.str());
}
