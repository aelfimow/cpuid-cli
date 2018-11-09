#include <sstream>

#include "IParser.h"
#include "Parser_0_0.h"
#include "cpuid_response.h"


Parser_0_0::Parser_0_0(cpuid_response const &data) :
    IParser { },
    maxInputValue { data.RAX() },
    vendorStr { }
{
    auto toChar = [](size_t value, size_t pos) { return static_cast<char>(value >> (8 * pos)); };

    const size_t charPos[] = { 0, 1, 2, 3 };

    for (auto pos: charPos)
    {
        vendorStr += toChar(data.RBX(), pos);
    }

    for (auto pos: charPos)
    {
        vendorStr += toChar(data.RDX(), pos);
    }

    for (auto pos: charPos)
    {
        vendorStr += toChar(data.RCX(), pos);
    }
}

Parser_0_0::~Parser_0_0()
{
}

parse_result_t Parser_0_0::parse() const
{
    parse_result_t result;

    std::stringstream ss;
    ss << "Maximum input value for basic CPUID: " << maxInputValue;

    result.push_back(ss.str());
    result.push_back(vendorStr);

    return result;
}
