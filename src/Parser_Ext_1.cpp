#include <bitset>
#include <map>

#include "IParser.h"
#include "Parser_Ext_1.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_Ext_1::Parser_Ext_1(cpuid_response const &data) :
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_result { }
{
}

Parser_Ext_1::~Parser_Ext_1()
{
}

parse_result_t Parser_Ext_1::parse()
{
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

void Parser_Ext_1::parseRAX(size_t value)
{
    bit_extractor extr { value };

    std::bitset<32> bits { extr.extract(31, 0) };

    ParserString pstr
    {
        "Extended Processor Signature and Feature Bits",
        bits.to_string()
    };

    m_result.push_back(pstr.str());
}

void Parser_Ext_1::parseRBX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_Ext_1::parseRCX(size_t value)
{
    bit_extractor extr { value };

    std::map<size_t, std::string> const table
    {
        { 0, "LAHF/SAHF available in 64-bit mode" },
        { 5, "LZCNT available" },
        { 8, "PREFETCHW available" }
    };

    for (auto &t: table)
    {
        if (extr.extract(t.first))
        {
            m_result.push_back(t.second);
        }
    }
}

void Parser_Ext_1::parseRDX(size_t value)
{
    bit_extractor extr { value };

    std::map<size_t, std::string> const table
    {
        { 11, "SYSCALL/SYSRET available in 64-bit mode" },
        { 20, "Execute Disable Bit available" },
        { 26, "1-GByte pages are available" },
        { 27, "RDTSCP and IA32_TSC_AUX are available" },
        { 29, "Intel(r) 64 Architecture available" }
    };

    for (auto &t: table)
    {
        if (extr.extract(t.first))
        {
            m_result.push_back(t.second);
        }
    }
}
