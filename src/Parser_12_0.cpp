#include <bitset>

#include "IParser.h"
#include "Parser_12_0.h"
#include "Parser_12_1.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_12_0::Parser_12_0(cpuid_response const &data) :
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_result { },
    m_next { (0 == data.RCX_Command()) ? nullptr : new Parser_12_1 { data } }
{
}

Parser_12_0::~Parser_12_0()
{
    delete m_next;
}

parse_result_t Parser_12_0::parse()
{
    if (m_next != nullptr)
    {
        return m_next->parse();
    }

    if (0 != m_result.size())
    {
        return m_result;
    }

    parseRAX(m_RAX);
    parseRBX(m_RBX);
    parseRCX(m_RCX);
    parseRDX(m_RDX);

    return m_result;
}

void Parser_12_0::parseRAX(size_t value)
{
    bit_extractor extr { value };

    if (extr.extract(0))
    {
        m_result.push_back("SGX1 leaf functions supported");
    }

    if (extr.extract(1))
    {
        m_result.push_back("SGX2 leaf functions supported");
    }
}

void Parser_12_0::parseRBX(size_t value)
{
    bit_extractor extr { value };

    std::bitset<32> bits { extr.extract(31, 0) };

    ParserString pstr
    {
        "Bit vector of supported extended SGX features",
        bits.to_string()
    };

    m_result.push_back(pstr.str());
}

void Parser_12_0::parseRCX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_12_0::parseRDX(size_t value)
{
    bit_extractor extr { value };

    {
        size_t size = (1U << extr.extract(7, 0));

        ParserString pstr
        {
            "Maximum supported enclave size in non-64-bit mode",
            size
        };

        m_result.push_back(pstr.str());
    }

    {
        size_t size = (1U << extr.extract(15, 8));

        ParserString pstr
        {
            "Maximum supported enclave size in 64-bit mode",
            size
        };

        m_result.push_back(pstr.str());
    }
}
