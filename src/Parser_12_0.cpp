#include "IParser.h"
#include "Parser_12_0.h"
#include "Parser_12_1.h"
#include "bit_extractor.h"
#include "cpuid_response.h"


Parser_12_0::Parser_12_0(cpuid_response const &data) :
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
        m_next = new Parser_12_1 { data };
    }
}

Parser_12_0::~Parser_12_0()
{
    delete m_next;
}

parse_result_t Parser_12_0::parse() const
{
    if (m_next != nullptr)
    {
        return m_next->parse();
    }

    return m_result;
}

void Parser_12_0::parseRAX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_12_0::parseRBX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_12_0::parseRCX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_12_0::parseRDX(size_t value)
{
    bit_extractor extr { value };
}