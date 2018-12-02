#include <sstream>

#include "IParser.h"
#include "Parser_3_0.h"
#include "cpuid_response.h"


Parser_3_0::Parser_3_0(cpuid_response const &data) :
    result { }
{
    std::stringstream ss;
    ss << "Processor Serial Number (on Pentium III only): ";
    ss << std::hex << data.RDX();
    ss << "; ";
    ss << std::hex << data.RCX();
    result.push_back(ss.str());
}

Parser_3_0::~Parser_3_0()
{
}

parse_result_t Parser_3_0::parse()
{
    return result;
}
