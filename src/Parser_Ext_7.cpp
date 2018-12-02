#include "IParser.h"
#include "Parser_Ext_7.h"
#include "bit_extractor.h"
#include "cpuid_response.h"


Parser_Ext_7::Parser_Ext_7(cpuid_response const &data) :
    m_result { }
{
    parseRAX(data.RAX());
    parseRBX(data.RBX());
    parseRCX(data.RCX());
    parseRDX(data.RDX());
}

Parser_Ext_7::~Parser_Ext_7()
{
}

parse_result_t Parser_Ext_7::parse() const
{
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
