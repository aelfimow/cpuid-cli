#include "IParser.h"
#include "Parser_F_0.h"
#include "Parser_F_1.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_F_0::Parser_F_0(cpuid_response const &data) :
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_result { },
    m_next { (0 == data.RCX_Command()) ? nullptr : new Parser_F_1 { data } }
{
}

Parser_F_0::~Parser_F_0()
{
    delete m_next;
}

parse_result_t Parser_F_0::parse()
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

void Parser_F_0::parseRAX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_F_0::parseRBX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Maximum range of RMID within this physical processor of all types",
        extr.extract(31, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_F_0::parseRCX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_F_0::parseRDX(size_t value)
{
    bit_extractor extr { value };

    if (extr.extract(1))
    {
        m_result.push_back("Supports L3 Cache Intel RDT Monitoring");
    }
}
