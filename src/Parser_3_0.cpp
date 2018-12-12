#include "IParser.h"
#include "Parser_3_0.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_3_0::Parser_3_0(cpuid_response const &data) :
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_result { }
{
}

Parser_3_0::~Parser_3_0()
{
}

parse_result_t Parser_3_0::parse()
{
    m_result.clear();

    ParserString pstr;

    pstr.clear()
        .prefix("Processor Serial Number (on Pentium III only)")
        .append(m_RDX)
        .append("; ")
        .append(m_RCX);

    m_result.push_back(pstr.str());

    return m_result;
}
