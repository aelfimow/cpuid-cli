#include <string>

#include "IParser.h"
#include "Parser_Ext_4.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "CpuRegString.h"
#include "ParserString.h"


Parser_Ext_4::Parser_Ext_4(cpuid_response const &data) :
    m_result { }
{
    CpuRegString RAX_str { data.RAX() };
    CpuRegString RBX_str { data.RBX() };
    CpuRegString RCX_str { data.RCX() };
    CpuRegString RDX_str { data.RDX() };

    std::string str;

    str += RAX_str.str();
    str += RBX_str.str();
    str += RCX_str.str();
    str += RDX_str.str();

    ParserString pstr { "Processor Brand String", str };

    m_result.push_back(pstr.str());
}

Parser_Ext_4::~Parser_Ext_4()
{
}

parse_result_t Parser_Ext_4::parse() const
{
    return m_result;
}
