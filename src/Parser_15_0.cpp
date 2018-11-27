#include "IParser.h"
#include "Parser_15_0.h"
#include "bit_extractor.h"
#include "cpuid_response.h"


Parser_15_0::Parser_15_0(cpuid_response const &data) :
    m_result { }
{
    parseRAX(data.RAX());
    parseRBX(data.RBX());
    parseRCX(data.RCX());
    parseRDX(data.RDX());
}

Parser_15_0::~Parser_15_0()
{
}

parse_result_t Parser_15_0::parse() const
{
    return m_result;
}

void Parser_15_0::parseRAX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_15_0::parseRBX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_15_0::parseRCX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_15_0::parseRDX(size_t value)
{
    bit_extractor extr { value };
}
