#include "IParser.h"
#include "Parser_Ext_8.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_Ext_8::Parser_Ext_8(cpuid_response const &data) :
    m_result { }
{
    parseRAX(data.RAX());
    parseRBX(data.RBX());
    parseRCX(data.RCX());
    parseRDX(data.RDX());
}

Parser_Ext_8::~Parser_Ext_8()
{
}

parse_result_t Parser_Ext_8::parse()
{
    return m_result;
}

void Parser_Ext_8::parseRAX(size_t value)
{
    bit_extractor extr { value };

    {
        ParserString pstr { "Physical Address Bits", extr.extract(7, 0) };

        m_result.push_back(pstr.str());
    }
    {
        ParserString pstr { "Linear Address Bits", extr.extract(15, 8) };

        m_result.push_back(pstr.str());
    }
}

void Parser_Ext_8::parseRBX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_Ext_8::parseRCX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_Ext_8::parseRDX(size_t value)
{
    bit_extractor extr { value };
}
