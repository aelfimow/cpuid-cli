#include "IParser.h"
#include "Parser_Ext_7.h"
#include "bit_extractor.h"
#include "cpuid_response.h"


Parser_Ext_7::Parser_Ext_7(cpuid_response const &data) :
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_result { }
{
}

Parser_Ext_7::~Parser_Ext_7()
{
}

parse_result_t Parser_Ext_7::parse()
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

void Parser_Ext_7::parseRAX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_Ext_7::parseRBX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_Ext_7::parseRCX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_Ext_7::parseRDX(size_t value)
{
    bit_extractor extr { value };

    if (extr.extract(8))
    {
        m_result.push_back("Invariant TSC available");
    }
}
