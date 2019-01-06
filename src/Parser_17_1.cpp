#include "IParser.h"
#include "Parser_17_1.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"
#include "CpuRegString.h"


Parser_17_1::Parser_17_1(cpuid_response const &data) :
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_result { },
    m_response_ok { false }
{
    size_t RCX_Command = data.RCX_Command();

    m_response_ok = ((RCX_Command >= 1) && (RCX_Command <= 3));
}

Parser_17_1::~Parser_17_1()
{
}

parse_result_t Parser_17_1::parse()
{
    m_result.clear();

    if (!m_response_ok)
    {
        return m_result;
    }

    CpuRegString RAX_str { m_RAX };
    CpuRegString RBX_str { m_RBX };
    CpuRegString RDX_str { m_RDX };
    CpuRegString RCX_str { m_RCX };

    std::string str;

    str += RAX_str.str();
    str += RBX_str.str();
    str += RDX_str.str();
    str += RCX_str.str();

    ParserString pstr { "Part of Vendor Brand String", str };

    m_result.push_back(pstr.str());

    return m_result;
}
