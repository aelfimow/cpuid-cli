#include <string>
#include <map>

#include "IParser.h"
#include "Parser_6_0.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_6_0::Parser_6_0(cpuid_response const &data) :
    result { }
{
    parseRAX(data.RAX());
    parseRBX(data.RBX());
    parseRCX(data.RCX());
    parseRDX(data.RDX());
}

Parser_6_0::~Parser_6_0()
{
}

parse_result_t Parser_6_0::parse() const
{
    return result;
}

void Parser_6_0::parseRAX(size_t value)
{
    bit_extractor extr { value };

    std::map<size_t, std::string> const table
    {
        {  0, "Digital temperature sensor is supported" },
        {  1, "Intel Turbo Boost Technology Available" },
        {  2, "ARAT. APIC-Timer-always-running feature is supported" },
        {  4, "PLN. Power limit notification controls are supported" },
        {  5, "ECMD. Clock modulation duty cycle extension is supported" },
        {  6, "PTM. Package thermal management is supported" },
        {  7, "HWP base registers are supported" },
        {  8, "HWP_Notification. IA32_HWP_INTERRUPT MSR is supported" },
        {  9, "HWP_Activity_Window. IA32_HWP_REQUEST[bits 41:32] is supported" },
        { 10, "HWP_Energy_Performance_Preference. IA32_HWP_REQUEST[bits 31:24] is supported" },
        { 11, "HWP_Package_Level_Request. IA32_HWP_REQUEST_PKG MSR is supported" },
        { 13, "HDC base registers are supported" }
    };

    for (auto &t: table)
    {
        if (extr.extract(t.first))
        {
            result.push_back(t.second);
        }
    }
}

void Parser_6_0::parseRBX(size_t value)
{
    bit_extractor extr { value };

    ParserString pstr
    {
        "Number of Interrupt Thresholds in Digital Thermal Sensor",
        extr.extract(3, 0)
    };

    result.push_back(pstr.str());
}

void Parser_6_0::parseRCX(size_t value)
{
    bit_extractor extr { value };

    if (extr.extract(0))
    {
        result.push_back("Hardware Coordination Feedback Capability");
    }

    if (extr.extract(3))
    {
        result.push_back("The processor supports performance-energy bias preference");
    }
}

void Parser_6_0::parseRDX(size_t value)
{
    bit_extractor extr { value };
}
