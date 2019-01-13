#include "IParser.h"
#include "Parser_17_0.h"
#include "Parser_17_1.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_17_0::Parser_17_0(cpuid_response const &data) :
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_result { },
    m_next { (0 == data.RCX_Command()) ? nullptr : new Parser_17_1 { data } }
{
}

Parser_17_0::~Parser_17_0()
{
    delete m_next;
}

parse_result_t Parser_17_0::parse()
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

void Parser_17_0::parseRAX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Maximum input value of supported sub-leaf", extr.extract(31, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_17_0::parseRBX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "SOC Vendor ID", extr.extract(15, 0)
    };

    m_result.push_back(pstr.str());

    m_result.push_back(
            extr.extract(16) ?
            "SOC Vendor ID field is assigned via an industry standard enumeration scheme" :
            "SOC Vendor ID field is assigned by Intel");
}

void Parser_17_0::parseRCX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Project ID", extr.extract(31, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_17_0::parseRDX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Stepping ID", extr.extract(31, 0)
    };

    m_result.push_back(pstr.str());
}
