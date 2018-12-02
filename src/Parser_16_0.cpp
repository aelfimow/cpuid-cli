#include "IParser.h"
#include "Parser_16_0.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_16_0::Parser_16_0(cpuid_response const &data) :
    m_result { }
{
    parseRAX(data.RAX());
    parseRBX(data.RBX());
    parseRCX(data.RCX());
    parseRDX(data.RDX());
}

Parser_16_0::~Parser_16_0()
{
}

parse_result_t Parser_16_0::parse()
{
    return m_result;
}

void Parser_16_0::parseRAX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Processor Base Frequency (in MHz)", extr.extract(15, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_16_0::parseRBX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Maximum Frequency (in MHz)", extr.extract(15, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_16_0::parseRCX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Bus (Reference) Frequency (in MHz)", extr.extract(15, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_16_0::parseRDX(size_t value)
{
    bit_extractor extr { value };
}
