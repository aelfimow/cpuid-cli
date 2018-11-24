#include <string>
#include <map>

#include "IParser.h"
#include "Parser_10_0.h"
#include "Parser_10_1.h"
#include "bit_extractor.h"
#include "cpuid_response.h"


Parser_10_0::Parser_10_0(cpuid_response const &data) :
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
        m_next = new Parser_10_1 { data };
    }
}

Parser_10_0::~Parser_10_0()
{
    delete m_next;
}

parse_result_t Parser_10_0::parse() const
{
    if (m_next != nullptr)
    {
        return m_next->parse();
    }

    return m_result;
}

void Parser_10_0::parseRAX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_10_0::parseRBX(size_t value)
{
    bit_extractor extr { value };

    std::map<size_t, std::string> const table
    {
        { 1, "Supports L3 Cache Allocation Technology" },
        { 2, "Supports L2 Cache Allocation Technology" },
        { 3, "Supports Memory Bandwidth Allocation" }
    };

    for (auto &t: table)
    {
        if (extr.extract(t.first))
        {
            m_result.push_back(t.second);
        }
    }
}

void Parser_10_0::parseRCX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_10_0::parseRDX(size_t value)
{
    bit_extractor extr { value };
}
