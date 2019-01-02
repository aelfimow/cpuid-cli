#include <string>
#include <map>

#include "IParser.h"
#include "Parser_Ext_6.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_Ext_6::Parser_Ext_6(cpuid_response const &data) :
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_result { }
{
}

Parser_Ext_6::~Parser_Ext_6()
{
}

parse_result_t Parser_Ext_6::parse()
{
    m_result.clear();

    parseRAX(m_RAX);
    parseRBX(m_RBX);
    parseRCX(m_RCX);
    parseRDX(m_RDX);

    return m_result;
}

void Parser_Ext_6::parseRAX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_Ext_6::parseRBX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_Ext_6::parseRCX(size_t value)
{
    bit_extractor extr { value };

    {
        ParserString pstr
        {
            "Cache Line size in bytes",
                extr.extract(7, 0)
        };

        m_result.push_back(pstr.str());
    }

    std::map<size_t, std::string> const table
    {
        { 0x00, "Disabled" },
        { 0x01, "Direct mapped" },
        { 0x02, "2-way" },
        { 0x04, "4-way" },
        { 0x06, "8-way" },
        { 0x08, "16-way" },
        { 0x0F, "Fully associative" }
    };

    for (auto &t: table)
    {
        if (t.first == extr.extract(15, 12))
        {
            ParserString pstr { "L2 Associativity", t.second };

            m_result.push_back(pstr.str());
        }
    }

    {
        ParserString pstr
        {
            "Cache size in 1K units",
            extr.extract(31, 16)
        };

        m_result.push_back(pstr.str());
    }
}

void Parser_Ext_6::parseRDX(size_t value)
{
    bit_extractor extr { value };
}
