#include <string>
#include <map>

#include "IParser.h"
#include "Parser_D_0.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_D_0::Parser_D_0(cpuid_response const &data) :
    result { }
{
    parseRAX(data.RAX());
    parseRBX(data.RBX());
    parseRCX(data.RCX());
    parseRDX(data.RDX());
}

Parser_D_0::~Parser_D_0()
{
}

parse_result_t Parser_D_0::parse() const
{
    return result;
}

void Parser_D_0::parseRAX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_D_0::parseRBX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_D_0::parseRCX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_D_0::parseRDX(size_t value)
{
    bit_extractor extr { value };
}
