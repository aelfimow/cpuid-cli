#include <bitset>
#include <map>

#include "IParser.h"
#include "Parser_1_0.h"
#include "cpuid_response.h"
#include "bit_extractor.h"
#include "ParserString.h"


Parser_1_0::Parser_1_0(cpuid_response const &data) :
    IParser { },
    m_RAX { data.RAX() },
    m_RBX { data.RBX() },
    m_RCX { data.RCX() },
    m_RDX { data.RDX() },
    m_result { }
{
}

Parser_1_0::~Parser_1_0()
{
}

parse_result_t Parser_1_0::parse()
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

void Parser_1_0::parseRAX(size_t value)
{
    bit_extractor bits { value };

    ParserString pstr;

    const size_t familyID = bits.extract(11, 8);

    {
        pstr.clear()
            .prefix("Stepping ID")
            .append(bits.extract(3, 0));

        m_result.push_back(pstr.str());
    }
    {
        std::map<size_t, std::string> typeField
        {
            { 0, "Original OEM Processor" },
            { 1, "Intel OverDrive(R) Processor" },
            { 2, "Dual processor" },
            { 3, "reserved" }
        };

        size_t const procType = bits.extract(13, 12);

        pstr.clear().prefix("Processor Type").append(typeField[procType]);

        m_result.push_back(pstr.str());
    }
    {
        size_t const extendedFamilyID = bits.extract(27, 20);

        size_t const sum = (familyID != 15) ? familyID : (extendedFamilyID + familyID);

        pstr.clear().prefix("Family ID").append(sum);

        m_result.push_back(pstr.str());
    }
    {
        const size_t modelID = bits.extract(7, 4);
        const size_t extendedModelID = bits.extract(19, 16);

        pstr.clear().prefix("Model ID");

        size_t const sum = ((familyID == 6) || (familyID == 15)) ?
            (16 * extendedModelID) + modelID : modelID;

        pstr.append(sum);

        m_result.push_back(pstr.str());
    }
}

void Parser_1_0::parseRBX(size_t value)
{
    bit_extractor bits { value };

    ParserString pstr;

    pstr.clear()
        .prefix("Brand index")
        .append(bits.extract(7, 0));

    m_result.push_back(pstr.str());

    pstr.clear()
        .prefix("CLFLUSH line size in bytes")
        .append(8 * bits.extract(15, 8));

    m_result.push_back(pstr.str());

    pstr.clear()
        .prefix("Maximum number of addressable IDs for logical processors")
        .append(bits.extract(23, 16));

    m_result.push_back(pstr.str());

    pstr.clear()
        .prefix("Initial APIC ID")
        .append(bits.extract(31, 24));

    m_result.push_back(pstr.str());
}

void Parser_1_0::parseRCX(size_t value)
{
    auto features { featuresRCX() };
    std::bitset<32> featureBits { value };

    for (auto feat: features)
    {
        auto bitpos { feat.first };
        auto str { feat.second };

        if (featureBits[bitpos])
        {
            m_result.push_back(str);
        }
    }
}

void Parser_1_0::parseRDX(size_t value)
{
    auto features { featuresRDX() };
    std::bitset<32> featureBits { value };

    for (auto feat: features)
    {
        auto bitpos { feat.first };
        auto str { feat.second };

        if (featureBits[bitpos])
        {
            m_result.push_back(str);
        }
    }
}

std::map<size_t, std::string> Parser_1_0::featuresRCX() const
{
    std::map<size_t, std::string> const features
    {
        {  0, "SSE3 extensions" },
        {  1, "Carryless multiplication (PCLMULQDQ)" },
        {  2, "64-bit DS area (DTES64)" },
        {  3, "MONITOR/MWAIT" },
        {  4, "CPL Qualified Debug Store (DS-CPL)" },
        {  5, "Virtual Machine Extensions (VMX)" },
        {  6, "Safer Mode Extensions (SMX)" },
        {  7, "Enhanced Intel SpeedStep(R) Technology" },
        {  8, "Thermal Monitor 2 (TM2)" },
        {  9, "SSSE3 Extensions" },
        { 10, "L1 Context ID (CNXT-ID)" },
        { 11, "SDBG" },
        { 12, "Fused Multiply Add (FMA)" },
        { 13, "CMPXCHG16B" },
        { 14, "xTPR Update Control" },
        { 15, "Perf/Debug Capability MSR (PDCM)" },
        { 17, "Process-context Identifiers (PCID)" },
        { 18, "Direct Cache Access (DCA)" },
        { 19, "SSE4.1" },
        { 20, "SSE4.2" },
        { 21, "x2APIC" },
        { 22, "MOVBE" },
        { 23, "POPCNT" },
        { 24, "TSC-Deadline" },
        { 25, "AES" },
        { 26, "XSAVE" },
        { 27, "OSXSAVE" },
        { 28, "AVX" },
        { 29, "F16C" },
        { 30, "RDRAND" }
    };

    return features;
}

std::map<size_t, std::string> Parser_1_0::featuresRDX() const
{
    std::map<size_t, std::string> const features
    {
        {  0, "x87 FPU on Chip" },
        {  1, "Virtual-8086 Mode Enhancement (VME)" },
        {  2, "Debugging Extensions (DE)" },
        {  3, "Page Size Extensions (PSE)" },
        {  4, "Time Stamp Counter (TSC)" },
        {  5, "RDMSR and WRMSR Support (MSR)" },
        {  6, "Physical Address Extensions (PAE)" },
        {  7, "Machine Check Exception (MCE)" },
        {  8, "CMPXCHG8B Instruction (CX8)" },
        {  9, "APIC on Chip (APIC)" },
        { 11, "SYSENTER and SYSEXIT (SEP)" },
        { 12, "Memory Type Range Registers (MTRR)" },
        { 13, "PTE Global Bit (PGE)" },
        { 14, "Machine Check Architecture (MCA)" },
        { 15, "Conditional Move/Compare Instruction (CMOV)" },
        { 16, "Page Attribute Table (PAT)" },
        { 17, "Page Size Extension (PSE-36)" },
        { 18, "Processor Serial Number (PSN)" },
        { 19, "CLFLUSH instruction (CLFSH)" },
        { 21, "Debug Store (DS)" },
        { 22, "Thermal Monitor and Clock Ctrl (ACPI)" },
        { 23, "MMX Technology" },
        { 24, "FXSAVE/FXRSTOR (FXSR)" },
        { 25, "SSE Extensions" },
        { 26, "SSE2 Extensions" },
        { 27, "Self Snoop (SS)" },
        { 28, "Multi-threading (HTT)" },
        { 29, "Thermal Monitor (TM)" },
        { 31, "Pend. Brk. EN. (PBE)" }
    };

    return features;
}
