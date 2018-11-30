#include <string>

#include "CpuRegString.h"
#include "bit_extractor.h"


CpuRegString::CpuRegString(size_t value) :
    m_str { }
{
    auto toChar = [](size_t value) { return static_cast<char>(value); };

    bit_extractor bits { value };

    m_str += toChar(bits.extract(7, 0));
    m_str += toChar(bits.extract(15, 8));
    m_str += toChar(bits.extract(23, 16));
    m_str += toChar(bits.extract(31, 24));
}

CpuRegString::~CpuRegString()
{
}

std::string CpuRegString::str() const
{
    return m_str;
}
