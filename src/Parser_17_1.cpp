#include "IParser.h"
#include "Parser_17_1.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"
#include "CpuRegString.h"


Parser_17_1::Parser_17_1(cpuid_response const &data) :
    m_result { },
    m_next { nullptr }
{
    size_t RCX_Command = data.RCX_Command();

    bool response_ok = ((RCX_Command >= 1) && (RCX_Command <= 3));

    if (!response_ok)
    {
        return;
    }

    CpuRegString RAX_str { data.RAX() };
    CpuRegString RBX_str { data.RBX() };
    CpuRegString RDX_str { data.RDX() };
    CpuRegString RCX_str { data.RCX() };

    std::string str;

    str += RAX_str.str();
    str += RBX_str.str();
    str += RDX_str.str();
    str += RCX_str.str();

    ParserString pstr { "Part of Vendor Brand String", str };

    m_result.push_back(pstr.str());
}

Parser_17_1::~Parser_17_1()
{
    delete m_next;
}

parse_result_t Parser_17_1::parse()
{
    if (m_next != nullptr)
    {
        return m_next->parse();
    }

    return m_result;
}
