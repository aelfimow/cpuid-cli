#include <string>
#include <map>

#include "IParser.h"
#include "Parser_14_0.h"
#include "Parser_14_1.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_14_0::Parser_14_0(cpuid_response const &data) :
    m_result { },
    m_next { nullptr }
{
    bool response_ok = (0 == data.RCX_Command());

    if (response_ok)
    {
        parseRAX(data.RAX());
        parseRBX(data.RBX());
        parseRCX(data.RCX());
        parseRDX(data.RDX());
    }
    else
    {
        m_next = new Parser_14_1 { data };
    }
}

Parser_14_0::~Parser_14_0()
{
    delete m_next;
}

parse_result_t Parser_14_0::parse() const
{
    if (m_next != nullptr)
    {
        return m_next->parse();
    }

    return m_result;
}

void Parser_14_0::parseRAX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Maximum sub-leaf",
        extr.extract(31, 0)
    };

    m_result.push_back(pstr.str());
}

void Parser_14_0::parseRBX(size_t value)
{
    bit_extractor extr { value };

    std::map<size_t, std::string> const table
    {
        { 0, "IA32_RTIT_CTL.CR3Filter can be set to 1; IA32_RTIT_CR3_MATCH MSR can be accessed" },
        { 1, "Configurable PSB and Cycle-Accurate Mode supported" },
        { 2, "IP/TraceStop filtering and preservation of Intel PT MSRs across warm reset supported" },
        { 3, "MTC timing packet and suppression of COFI-based packets supported" },
        { 4, "PTWRITE supported" },
        { 5, "Power Event Trace supported" }
    };

    for (auto &t: table)
    {
        if (extr.extract(t.first))
        {
            m_result.push_back(t.second);
        }
    }
}

void Parser_14_0::parseRCX(size_t value)
{
    bit_extractor extr { value };

    std::map<size_t, std::string> const table
    {
        { 0, "Tracing can be enabled" },
        { 1, "ToPA tables can hold any number of output entries" },
        { 2, "Single-Range Output scheme supported" },
        { 3, "Output to Trace Transport subsystem supported" },
        { 31, "Generated packets which contain IP payloads have LIP values, which include the CS base component" }
    };

    for (auto &t: table)
    {
        if (extr.extract(t.first))
        {
            m_result.push_back(t.second);
        }
    }
}

void Parser_14_0::parseRDX(size_t value)
{
    bit_extractor extr { value };
}
