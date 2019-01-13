#include "IParser.h"
#include "Parser_10_3.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_10_3::Parser_10_3(cpuid_response const &data) :
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_result { },
    m_response_ok { 3 == data.RCX_Command() }
{
}

Parser_10_3::~Parser_10_3()
{
}

parse_result_t Parser_10_3::parse()
{
    if (0 != m_result.size())
    {
        return m_result;
    }

    parseRAX(m_RAX);
    parseRBX(m_RBX);
    parseRCX(m_RCX);
    parseRDX(m_RDX);

    return m_result;
}

void Parser_10_3::parseRAX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Maximum MBA throttling value supported for ResID 3",
        1 + extr.extract(11, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_10_3::parseRBX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_10_3::parseRCX(size_t value)
{
    bit_extractor extr { value };

    if (extr.extract(2))
    {
        m_result.push_back("Response of the delay values is linear");
    }
}

void Parser_10_3::parseRDX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Highest COS number supported for ResID 3",
        extr.extract(15, 0)
    };

    m_result.push_back(pstr.str());
}
