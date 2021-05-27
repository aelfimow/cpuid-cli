#include <string>
#include <map>

#include "IParser.h"
#include "Parser_7_0.h"
#include "bit_extractor.h"
#include "cpuid_response.h"
#include "ParserString.h"


Parser_7_0::Parser_7_0(cpuid_response const &data) :
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_result { }
{
}

Parser_7_0::~Parser_7_0()
{
}

parse_result_t Parser_7_0::parse()
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

void Parser_7_0::parseRAX(size_t value)
{
    ParserString pstr { "Maximum input value for supported sub-leaves", value };
    m_result.push_back(pstr.str());
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
        { 16, "AVX512F" },
        { 17, "AVX512DQ" },
        { 18, "RDSEED" },
        { 19, "ADX" },
        { 20, "SMAP. Supports Supervisor-Mode Access Prevention (and the CLAC/STAC instructions)" },
        { 21, "AVX512_IFMA" },
        { 22, "Reserved" },
        { 23, "CLFLUSHOPT" },
        { 24, "CLWB" },
        { 25, "Intel Processor Trace." },
        { 26, "AVX512PF" },
        { 27, "AVX512ER" },
        { 28, "AVX512CD" },
        { 29, "SHA. Secure Hash Algorithm Extensions" },
        { 30, "AVX512BW" },
        { 31, "AVX512VL" }
    };

    for (auto &t: table)
    {
        if (extr.extract(t.first))
        {
            m_result.push_back(t.second);
        }
    }
}

void Parser_7_0::parseRCX(size_t value)
{
    bit_extractor extr { value };

    std::map<size_t, std::string> const table
    {
        { 0, "PREFETCHWT1" },
        { 1, "AVX512_VBMI" },
        { 2, "UMIP. Supports user-mode instruction prevention" },
        { 3, "PKU. Supports protection keys for user-mode pages" },
        { 4, "OSPKE. OS has set CR4.PKE to enable protection keys (and the RDPKRU/WRPKRU instructions)" },
        { 5, "WAITPKG" },
        { 6, "AVX512_VBMI2" },
        { 7, "CET_SS. Supports CET shadow stack features" },
        { 8, "GFNI" },
        { 9, "VAES" },
        { 10, "VPCLMULQDQ" },
        { 11, "AVX512_VNNI" },
        { 12, "AVX512_BITALG" },
        { 13, "TME_EN" },
        { 14, "AVX512_VPOPCNTDQ" },
        { 15, "Reserved" },
        { 16, "LA57. Supports 57-bit linear addresses and five-level paging" },
        { 22, "RDPID and IA32_TSC_AUX are available" },
        { 23, "KL. Supports Key Locker" },
        { 24, "Reserved" },
        { 25, "CLDEMOTE. Supports cache line demote" },
        { 26, "Reserved" },
        { 27, "MOVDIRI. Supports MOVDIRI" },
        { 28, "MOVDIR64B. Supports MOVDIR64B" },
        { 29, "Reserved" },
        { 30, "SGX_LC. Supports SGX Launch Configuration" },
        { 31, "PKS. Supports protection keys for supervisor-mode pages" }
    };

    for (auto &t: table)
    {
        if (extr.extract(t.first))
        {
            m_result.push_back(t.second);
        }
    }

    ParserString pstr
    {
        "The value of MAWAU used by the BNDLDX and BNDSTX instructions in 64-bit mode",
        extr.extract(21, 17)
    };

    m_result.push_back(pstr.str());
}

void Parser_7_0::parseRDX(size_t value)
{
    bit_extractor extr { value };

    std::map<size_t, std::string> const table
    {
        { 2, "AVX512_4VNNIW" },
        { 3, "AVX512_4FMAPS" },
        { 4, "Fast Short REP MOV" },
        { 8, "AVX512_VP2INTERSECT" },
        { 10, "MD_CLEAR supported" },
        { 15, "Hybrid. The processor is identified as a hybrid part" },
        { 18, "PCONFIG. Supports PCONFIG" },
        { 20, "CET_IBT. Supports CET indirect branch tracking features" },
        { 26, "Enumerates support for IBRS and IBPB" },
        { 27, "Enumerates support for single thread indirect branch predictors (STIBP)" },
        { 28, "Enumerates support for L1D_FLUSH" },
        { 29, "Enumerates support for the IA32_ARCH_CAPABILITIES MSR" },
        { 30, "Enumerates support for the IA32_CORE_CAPABILITIES MSR" },
        { 31, "Enumerates support for Speculative Store Bypass Disable (SSBD)" }
    };

    for (auto &t: table)
    {
        if (extr.extract(t.first))
        {
            m_result.push_back(t.second);
        }
    }
}
