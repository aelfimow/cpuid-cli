#include <sstream>

#include "IParser.h"
#include "Parser_0_0.h"
#include "cpuid_response.h"
#include "bit_extractor.h"
#include "ParserString.h"
#include "CpuRegString.h"


Parser_0_0::Parser_0_0(cpuid_response const &data) :
    IParser { },
    maxInputValue { data.RAX() },
    vendorStr { }
{
    CpuRegString RBX_str { data.RBX() };
    CpuRegString RDX_str { data.RDX() };
    CpuRegString RCX_str { data.RCX() };

    vendorStr += RBX_str.str();
    vendorStr += RDX_str.str();
    vendorStr += RCX_str.str();
}

Parser_0_0::~Parser_0_0()
{
}

parse_result_t Parser_0_0::parse()
{
    parse_result_t result;

    ParserString pstr { "Maximum input value for basic CPUID", maxInputValue };

    result.push_back(pstr.str());
    result.push_back(vendorStr);

    return result;
}
