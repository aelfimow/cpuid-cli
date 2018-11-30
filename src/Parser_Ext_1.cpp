#include "IParser.h"
#include "Parser_Ext_1.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_Ext_1::Parser_Ext_1(cpuid_response const &data) :
    m_result { }
{
    parseRAX(data.RAX());
    parseRBX(data.RBX());
    parseRCX(data.RCX());
    parseRDX(data.RDX());
}

Parser_Ext_1::~Parser_Ext_1()
{
}

parse_result_t Parser_Ext_1::parse() const
{
    return m_result;
}

void Parser_Ext_1::parseRAX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_Ext_1::parseRBX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_Ext_1::parseRCX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_Ext_1::parseRDX(size_t value)
{
    bit_extractor extr { value };
}
