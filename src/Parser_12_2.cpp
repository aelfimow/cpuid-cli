#include "IParser.h"
#include "Parser_12_2.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_12_2::Parser_12_2(cpuid_response const &data) :
    m_result { },
    m_next { nullptr }
{
    bool response_ok = (2 <= data.RCX_Command());

    if (!response_ok)
    {
        return;
    }

    bit_extractor extr { data.RAX() };

    bool subleaf_valid = (1 == extr.extract(3, 0));

    if (!subleaf_valid)
    {
        return;
    }

    bit_extractor extr1 { data.RAX() };
    bit_extractor extr2 { data.RBX() };

    size_t physAddr1 = (extr2.extract(19, 0) << 32) + (extr1.extract(31, 12) << 12);

    {
        ParserString pstr
        {
            "Physical address of the base of the EPC section",
            physAddr1
        };

        m_result.push_back(pstr.str());
    }

    bit_extractor extr3 { data.RCX() };
    bit_extractor extr4 { data.RDX() };

    size_t size = (extr4.extract(19, 0) << 32) + (extr3.extract(31, 12) << 12);

    {
        ParserString pstr
        {
            "Size of the corresponding EPC section within the Processor Reserved Memory",
            size
        };

        m_result.push_back(pstr.str());
    }
}

Parser_12_2::~Parser_12_2()
{
    delete m_next;
}

parse_result_t Parser_12_2::parse() const
{
    if (m_next != nullptr)
    {
        return m_next->parse();
    }

    return m_result;
}
