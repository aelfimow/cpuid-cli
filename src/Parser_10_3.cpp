#include "IParser.h"
#include "Parser_10_3.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_10_3::Parser_10_3(cpuid_response const &data) :
    m_result { },
    m_next { nullptr }
{
    bool response_ok = (3 == data.RCX_Command());

    if (response_ok)
    {
        parseRAX(data.RAX());
        parseRBX(data.RBX());
        parseRCX(data.RCX());
        parseRDX(data.RDX());
    }
}

Parser_10_3::~Parser_10_3()
{
    delete m_next;
}

parse_result_t Parser_10_3::parse()
{
    if (m_next != nullptr)
    {
        return m_next->parse();
    }

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
