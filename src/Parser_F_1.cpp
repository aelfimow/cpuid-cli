#include <string>
#include <map>

#include "IParser.h"
#include "Parser_F_1.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_F_1::Parser_F_1(cpuid_response const &data) :
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_result { },
    m_response_ok { 1 == data.RCX_Command() }
{
}

Parser_F_1::~Parser_F_1()
{
}

parse_result_t Parser_F_1::parse()
{
    if (!m_response_ok)
    {
        return m_result;
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

void Parser_F_1::parseRAX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_F_1::parseRBX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Conversion factor from reported IA32_QM_CTR value to occupancy metric",
        extr.extract(31, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_F_1::parseRCX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Maximum range (zero-based) of RMID of this resource type",
        extr.extract(31, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_F_1::parseRDX(size_t value)
{
    bit_extractor extr { value };

    std::map<size_t, std::string> const table
    {
        { 0, "Supports L3 occupancy monitoring" },
        { 1, "Supports L3 Total Bandwidth monitoring" },
        { 2, "Supports L3 Local Bandwidth monitoring" }
    };

    for (auto &t: table)
    {
        if (extr.extract(t.first))
        {
            m_result.push_back(t.second);
        }
    }
}
