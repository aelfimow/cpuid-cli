#include "IParser.h"
#include "Parser_Ext_6.h"
#include "bit_extractor.h"
#include "cpuid_response.h"


Parser_Ext_6::Parser_Ext_6(cpuid_response const &data) :
    m_result { }
{
    parseRAX(data.RAX());
    parseRBX(data.RBX());
    parseRCX(data.RCX());
    parseRDX(data.RDX());
}

Parser_Ext_6::~Parser_Ext_6()
{
}

parse_result_t Parser_Ext_6::parse() const
{
    return m_result;
}

void Parser_Ext_6::parseRAX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_Ext_6::parseRBX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_Ext_6::parseRCX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_Ext_6::parseRDX(size_t value)
{
    bit_extractor extr { value };
}
