#include <bitset>

#include "IParser.h"
#include "Parser_14_1.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_14_1::Parser_14_1(cpuid_response const &data) :
    m_result { },
    m_next { nullptr }
{
    bool response_ok = (1 == data.RCX_Command());

    if (response_ok)
    {
        parseRAX(data.RAX());
        parseRBX(data.RBX());
        parseRCX(data.RCX());
        parseRDX(data.RDX());
    }
}

Parser_14_1::~Parser_14_1()
{
    delete m_next;
}

parse_result_t Parser_14_1::parse() const
{
    if (m_next != nullptr)
    {
        return m_next->parse();
    }

    return m_result;
}

void Parser_14_1::parseRAX(size_t value)
{
    bit_extractor extr { value };

    {
        ParserString pstr
        {
            "Number of configurable Address Ranges for filtering",
            extr.extract(2, 0)
        };

        m_result.push_back(pstr.str());
    }

    {
        std::bitset<16> bits { extr.extract(31, 16) };

        ParserString pstr
        {
            "Bitmap of supported MTC period encodings",
            bits.to_string()
        };

        m_result.push_back(pstr.str());
    }
}

void Parser_14_1::parseRBX(size_t value)
{
    bit_extractor extr { value };

    {
        std::bitset<16> bits { extr.extract(15, 0) };

        ParserString pstr
        {
            "Bitmap of supported Cycle Threshold value encodings",
            bits.to_string()
        };

        m_result.push_back(pstr.str());
    }

    {
        std::bitset<16> bits { extr.extract(31, 16) };

        ParserString pstr
        {
            "Bitmap of supported Configurable PSB frequency encodings",
            bits.to_string()
        };

        m_result.push_back(pstr.str());
    }
}

void Parser_14_1::parseRCX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_14_1::parseRDX(size_t value)
{
    bit_extractor extr { value };
}
