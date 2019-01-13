#include <string>
#include <map>

#include "IParser.h"
#include "Parser_9_0.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_9_0::Parser_9_0(cpuid_response const &data) :
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_result { }
{
}

Parser_9_0::~Parser_9_0()
{
}

parse_result_t Parser_9_0::parse()
{
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

void Parser_9_0::parseRAX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Value of bits [31:0] of IA32_PLATFORM_DCA_CAP MSR",
        extr.extract(31, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_9_0::parseRBX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_9_0::parseRCX(size_t value)
{
    bit_extractor extr { value };
}

void Parser_9_0::parseRDX(size_t value)
{
    bit_extractor extr { value };
}
