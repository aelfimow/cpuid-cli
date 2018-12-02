#include "IParser.h"
#include "Parser_Ext_0.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_Ext_0::Parser_Ext_0(cpuid_response const &data) :
    m_result { }
{
    parseRAX(data.RAX());
    parseRBX(data.RBX());
    parseRCX(data.RCX());
    parseRDX(data.RDX());
}

Parser_Ext_0::~Parser_Ext_0()
{
}

parse_result_t Parser_Ext_0::parse()
{
    return m_result;
}

void Parser_Ext_0::parseRAX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Maximum Input Value for Extended Function CPUID Information",
        extr.extract(30, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_Ext_0::parseRBX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_Ext_0::parseRCX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_Ext_0::parseRDX(size_t value)
{
    bit_extractor extr { value };
}
