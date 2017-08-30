#include <sstream>

#include "Parser_0_0.h"


Parser_0_0::Parser_0_0(size_t RAX, size_t RBX, size_t RCX, size_t RDX) :
    maxInputValue { RAX },
    vendorStr { }
{
    auto toChar = [](size_t value, size_t pos) { return static_cast<char>(value >> (8 * pos)); };

    const size_t charPos[] = { 3, 2, 1, 0 };

    for (auto pos: charPos)
    {
        vendorStr += toChar(RBX, pos);
    }

    for (auto pos: charPos)
    {
        vendorStr += toChar(RCX, pos);
    }

    for (auto pos: charPos)
    {
        vendorStr += toChar(RDX, pos);
    }
}

Parser_0_0::~Parser_0_0()
{
}

std::list<std::string> Parser_0_0::get() const
{
    std::list<std::string> result;

    std::stringstream ss;
    ss << "Maximum input value for basic CPUID: " << maxInputValue;

    result.push_back(ss.str());
    result.push_back(vendorStr);

    return result;
}
