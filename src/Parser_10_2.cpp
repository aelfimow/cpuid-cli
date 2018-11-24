#include "IParser.h"
#include "Parser_10_2.h"
#include "Parser_10_3.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_10_2::Parser_10_2(cpuid_response const &data) :
    m_result { },
    m_next { nullptr }
{
    bool response_ok = (2 == data.RCX_Command());

    if (response_ok)
    {
        parseRAX(data.RAX());
        parseRBX(data.RBX());
        parseRCX(data.RCX());
        parseRDX(data.RDX());
    }
    else
    {
        m_next = new Parser_10_3 { data };
    }
}

Parser_10_2::~Parser_10_2()
{
    delete m_next;
}

parse_result_t Parser_10_2::parse() const
{
    if (m_next != nullptr)
    {
        return m_next->parse();
    }

    return m_result;
}

void Parser_10_2::parseRAX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Length of the capacity bit mask for ResID 2",
        1 + extr.extract(4, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_10_2::parseRBX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Bit-granular map of isolation/contention of allocation units",
        extr.extract(31, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_10_2::parseRCX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_10_2::parseRDX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Highest COS number supported for ResID 2",
        extr.extract(15, 0)
    };

    m_result.push_back(pstr.str());
}
