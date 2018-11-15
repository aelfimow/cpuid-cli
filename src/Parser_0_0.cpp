#include <sstream>

#include "IParser.h"
#include "Parser_0_0.h"
#include "cpuid_response.h"
#include "bit_extractor.h"
#include "ParserString.h"


Parser_0_0::Parser_0_0(cpuid_response const &data) :
    IParser { },
    maxInputValue { data.RAX() },
    vendorStr { }
{
    auto toChar = [](size_t value) { return static_cast<char>(value); };

    size_t const regs[3] { data.RBX(), data.RDX(), data.RCX() };

    for (auto r: regs)
    {
        bit_extractor bits { r };

        vendorStr += toChar(bits.extract(7, 0));
        vendorStr += toChar(bits.extract(15, 8));
        vendorStr += toChar(bits.extract(23, 16));
        vendorStr += toChar(bits.extract(31, 24));
    }
}

Parser_0_0::~Parser_0_0()
{
}

parse_result_t Parser_0_0::parse() const
{
    parse_result_t result;

    ParserString pstr { "Maximum input value for basic CPUID", maxInputValue };

    result.push_back(pstr.str());
    result.push_back(vendorStr);

    return result;
}
