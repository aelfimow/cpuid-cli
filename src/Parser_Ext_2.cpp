#include <string>

#include "IParser.h"
#include "Parser_Ext_2.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "CpuRegString.h"
#include "ParserString.h"


Parser_Ext_2::Parser_Ext_2(cpuid_response const &data) :
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_result { }
{
}

Parser_Ext_2::~Parser_Ext_2()
{
}

parse_result_t Parser_Ext_2::parse()
{
    if (0 != m_result.size())
    {
        return m_result;
    }

    CpuRegString RAX_str { m_RAX };
    CpuRegString RBX_str { m_RBX };
    CpuRegString RCX_str { m_RCX };
    CpuRegString RDX_str { m_RDX };

    std::string str;

    str += RAX_str.str();
    str += RBX_str.str();
    str += RCX_str.str();
    str += RDX_str.str();

    ParserString pstr { "Processor Brand String", str };

    m_result.push_back(pstr.str());

    return m_result;
}
