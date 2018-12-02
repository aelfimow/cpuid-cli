#include <string>
#include <map>

#include "IParser.h"
#include "Parser_7_0.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_7_0::Parser_7_0(cpuid_response const &data) :
    result { },
    infoAvail { false }
{
    parseRAX(data.RAX());

    if (infoAvail)
    {
        parseRBX(data.RBX());
        parseRCX(data.RCX());
        parseRDX(data.RDX());
    }
}

Parser_7_0::~Parser_7_0()
{
}

parse_result_t Parser_7_0::parse()
{
    return result;
}

void Parser_7_0::parseRAX(size_t value)
{
    ParserString pstr { "Maximum input value for supported sub-leaves", value };
    result.push_back(pstr.str());

    infoAvail = (value != 0);
}

void Parser_7_0::parseRBX(size_t value)
{
    bit_extractor extr { value };

    std::map<size_t, std::string> const table
    {
        { 0, "FSGSBASE. Supports RDFSBASE/RDGSBASE/WRFSBASE/WRGSBASE" },
        { 1, "IA32_TSC_ADJUST MSR is supported" },
        { 2, "SGX. Supports Software Guard Extensions" },
        { 3, "BMI1" },
        { 4, "HLE" },
        { 5, "AVX2" },
        { 6, "FDP_EXCPTN_ONLY. x87 FPU Data Pointer updated only on x87 exceptions" },
        { 7, "SMEP. Supports Supervisor-Mode Execution Prevention" },
        { 8, "BMI2" },
        { 9, "Supports Enhanced REP MOVSB/STOSB" },
        { 10, "Supports INVPCID instruction" },
        { 11, "RTM" },
        { 12, "RDT-M. Resource Director Technology Monitoring capability" },
        { 13, "Deprecates FPU CS and FPU DS values" },
        { 14, "MPX. Memory Protection Extensions" },
        { 15, "RDT-A. Resource Director Technology Allocation capability" },
        { 18, "RDSEED" },
        { 19, "ADX" },
        { 20, "SMAP. Supports Supervisor-Mode Access Prevention (and the CLAC/STAC instructions)" },
        { 23, "CLFLUSHOPT" },
        { 24, "CLWB" },
        { 25, "Intel Processor Trace." },
        { 29, "SHA. Secure Hash Algorithm Extensions" }
    };

    for (auto &t: table)
    {
        if (extr.extract(t.first))
        {
            result.push_back(t.second);
        }
    }
}

void Parser_7_0::parseRCX(size_t value)
{
    bit_extractor extr { value };

    std::map<size_t, std::string> const table
    {
        {  0, "PREFETCHWT1" },
        {  2, "UMIP. Supports user-mode instruction prevention" },
        {  3, "PKU. Supports protection keys for user-mode pages" },
        {  4, "OSPKE. OS has set CR4.PKE to enable protection keys (and the RDPKRU/WRPKRU instructions)" },
        { 22, "RDPID. Supports Read Processor ID" },
        { 30, "SGX_LC. Supports SGX Launch Configuration" }
    };

    for (auto &t: table)
    {
        if (extr.extract(t.first))
        {
            result.push_back(t.second);
        }
    }

    ParserString pstr
    {
        "The value of MAWAU used by the BNDLDX and BNDSTX instructions in 64-bit mode",
        extr.extract(21, 17)
    };

    result.push_back(pstr.str());
}

void Parser_7_0::parseRDX(size_t value)
{
    bit_extractor extr { value };
}
