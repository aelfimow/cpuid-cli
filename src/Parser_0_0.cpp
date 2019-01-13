#include <sstream>

#include "IParser.h"
#include "Parser_0_0.h"
#include "cpuid_response.h"
#include "bit_extractor.h"
#include "ParserString.h"
#include "CpuRegString.h"


Parser_0_0::Parser_0_0(cpuid_response const &data) :
    IParser { },
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_result { }
{
}

Parser_0_0::~Parser_0_0()
{
}

parse_result_t Parser_0_0::parse()
{
    if (0 != m_result.size())
    {
        return m_result;
    }

    ParserString pstr;

    {
        pstr.clear()
            .prefix("Maximum input value for basic CPUID")
            .append(m_RAX);

        m_result.push_back(pstr.str());
    }

    {
        CpuRegString RBX_str { m_RBX };
        CpuRegString RDX_str { m_RDX };
        CpuRegString RCX_str { m_RCX };

        pstr.clear()
            .prefix("Vendor")
            .append(RBX_str.str())
            .append(RDX_str.str())
            .append(RCX_str.str());

        m_result.push_back(pstr.str());
    }

    return m_result;
}
