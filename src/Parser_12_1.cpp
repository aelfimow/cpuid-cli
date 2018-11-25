#include "IParser.h"
#include "Parser_12_1.h"
#include "Parser_12_2.h"
#include "bit_extractor.h"
#include "cpuid_response.h"


Parser_12_1::Parser_12_1(cpuid_response const &data) :
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
    else
    {
        m_next = new Parser_12_2 { data };
    }
}

Parser_12_1::~Parser_12_1()
{
    delete m_next;
}

parse_result_t Parser_12_1::parse() const
{
    if (m_next != nullptr)
    {
        return m_next->parse();
    }

    return m_result;
}

void Parser_12_1::parseRAX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_12_1::parseRBX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_12_1::parseRCX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_12_1::parseRDX(size_t value)
{
    bit_extractor extr { value };
}