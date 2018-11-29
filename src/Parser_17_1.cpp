#include "IParser.h"
#include "Parser_17_1.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_17_1::Parser_17_1(cpuid_response const &data) :
    m_result { },
    m_next { nullptr }
{
    size_t RCX_Command = data.RCX_Command();

    bool response_ok = ((RCX_Command >= 1) && (RCX_Command <= 3));

    if (!response_ok)
    {
        return;
    }

    auto toChar = [](size_t value)
    {
        return (value == 0) ? ' ' : static_cast<char>(value);
    };

    size_t const regs[4] { data.RAX(), data.RBX(), data.RDX(), data.RCX() };

    std::string str;

    for (auto r: regs)
    {
        bit_extractor bits { r };

        str += toChar(bits.extract(7, 0));
        str += toChar(bits.extract(15, 8));
        str += toChar(bits.extract(23, 16));
        str += toChar(bits.extract(31, 24));
    }

    ParserString pstr { "Part of Vendor Brand String", str };

    m_result.push_back(pstr.str());
}

Parser_17_1::~Parser_17_1()
{
    delete m_next;
}

parse_result_t Parser_17_1::parse() const
{
    if (m_next != nullptr)
    {
        return m_next->parse();
    }

    return m_result;
}
