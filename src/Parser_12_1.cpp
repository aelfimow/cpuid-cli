#include <bitset>

#include "IParser.h"
#include "Parser_12_1.h"
#include "Parser_12_2.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_12_1::Parser_12_1(cpuid_response const &data) :
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_result { },
    m_next { (1 == data.RCX_Command()) ? nullptr : new Parser_12_2 { data } }
{
}

Parser_12_1::~Parser_12_1()
{
    delete m_next;
}

parse_result_t Parser_12_1::parse()
{
    if (m_next != nullptr)
    {
        return m_next->parse();
    }

    m_result.clear();

    parseRAX(m_RAX);
    parseRBX(m_RBX);
    parseRCX(m_RCX);
    parseRDX(m_RDX);

    return m_result;
}

void Parser_12_1::parseRAX(size_t value)
{
    bit_extractor extr { value };

    std::bitset<32> bits { extr.extract(31, 0) };

    ParserString pstr
    {
        "Bits of SECS.ATTRIBUTES[31:0] that software can set with ECREATE",
        bits.to_string()
    };

    m_result.push_back(pstr.str());
}

void Parser_12_1::parseRBX(size_t value)
{
    bit_extractor extr { value };

    std::bitset<32> bits { extr.extract(31, 0) };

    ParserString pstr
    {
        "Bits of SECS.ATTRIBUTES[63:32] that software can set with ECREATE",
        bits.to_string()
    };

    m_result.push_back(pstr.str());
}

void Parser_12_1::parseRCX(size_t value)
{
    bit_extractor extr { value };

    std::bitset<32> bits { extr.extract(31, 0) };

    ParserString pstr
    {
        "Bits of SECS.ATTRIBUTES[95:64] that software can set with ECREATE",
        bits.to_string()
    };

    m_result.push_back(pstr.str());
}

void Parser_12_1::parseRDX(size_t value)
{
    bit_extractor extr { value };

    std::bitset<32> bits { extr.extract(31, 0) };

    ParserString pstr
    {
        "Bits of SECS.ATTRIBUTES[127:96] that software can set with ECREATE",
        bits.to_string()
    };

    m_result.push_back(pstr.str());
}
