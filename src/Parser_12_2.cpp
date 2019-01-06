#include "IParser.h"
#include "Parser_12_2.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_12_2::Parser_12_2(cpuid_response const &data) :
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_result { },
    m_response_ok { 2 <= data.RCX_Command() }
{
}

Parser_12_2::~Parser_12_2()
{
}

parse_result_t Parser_12_2::parse()
{
    m_result.clear();

    if (!m_response_ok)
    {
        return m_result;
    }

    bit_extractor extr { m_RAX };

    bool subleaf_valid = (1 == extr.extract(3, 0));

    if (!subleaf_valid)
    {
        return m_result;
    }

    bit_extractor extr1 { m_RAX };
    bit_extractor extr2 { m_RBX };

    size_t physAddr1 = (extr2.extract(19, 0) << 32) + (extr1.extract(31, 12) << 12);

    {
        ParserString pstr
        {
            "Physical address of the base of the EPC section",
            physAddr1
        };

        m_result.push_back(pstr.str());
    }

    bit_extractor extr3 { m_RCX };
    bit_extractor extr4 { m_RDX };

    size_t size = (extr4.extract(19, 0) << 32) + (extr3.extract(31, 12) << 12);

    {
        ParserString pstr
        {
            "Size of the corresponding EPC section within the Processor Reserved Memory",
            size
        };

        m_result.push_back(pstr.str());
    }

    return m_result;
}
