#include <sstream>
#include <bitset>
#include <map>

#include "IParser.h"
#include "Parser_1_0.h"
#include "cpuid_response.h"


Parser_1_0::Parser_1_0(cpuid_response const &data) :
    IParser { },
    result { }
{
    parseRAX(data.RAX());
    parseRBX(data.RBX());
    parseRCX(data.RCX());
    parseRDX(data.RDX());
}

Parser_1_0::~Parser_1_0()
{
}

parse_result_t Parser_1_0::parse() const
{
    return result;
}

void Parser_1_0::parseRAX(size_t value)
{
    const size_t mask2bit = 0x0003;
    const size_t mask4bit = 0x000F;
    const size_t mask8bit = 0x00FF;

    const size_t steppingID = value & mask4bit;
    const size_t modelID = (value >> 4) & mask4bit;
    const size_t familyID = (value >> 8) & mask4bit;
    const size_t procType = (value >> 12) & mask2bit;
    const size_t extendedModelID = (value >> 16) & mask4bit;
    const size_t extendedFamilyID = (value >> 20) & mask8bit;

    {
        std::stringstream ss;
        ss << std::hex << steppingID;
        std::string str { "Stepping ID: " };
        str += ss.str();
        result.push_back(str);
    }
    {
        std::map<size_t, std::string> typeField;
        typeField[0] = "Original OEM Processor";
        typeField[1] = "Intel OverDrive(R) Processor";
        typeField[2] = "Dual processor";
        typeField[3] = "reserved";
        std::string str { "Processor Type: " };
        str += typeField[procType];
        result.push_back(str);
    }
    {
        std::string str { "Family ID: " };
        std::stringstream ss;
        if (familyID != 15)
        {
            ss << std::hex << familyID;
        }
        else
        {
            size_t sum = extendedFamilyID + familyID;
            ss << std::hex << sum;
        }
        str += ss.str();
        result.push_back(str);
    }
    {
        std::string str { "Model ID: " };
        std::stringstream ss;
        if ((familyID == 6) || (familyID == 15))
        {
            size_t sum = (extendedModelID << 4) + modelID;
            ss << std::hex << sum;
        }
        else
        {
            ss << std::hex << modelID;
        }
        str += ss.str();
        result.push_back(str);
    }
}

void Parser_1_0::parseRBX(size_t value)
{
    const uint8_t byte0 = static_cast<uint8_t>(value);
    const uint8_t byte1 = static_cast<uint8_t>(value >> 8);
    const uint8_t byte2 = static_cast<uint8_t>(value >> 16);
    const uint8_t byte3 = static_cast<uint8_t>(value >> 24);

    {
        const size_t brandIndex = static_cast<size_t>(byte0);
        std::stringstream ss;
        ss << "Brand index: " << brandIndex;
        result.push_back(ss.str());
    }
    {
        const size_t lineSize = 8 * static_cast<size_t>(byte1);
        std::stringstream ss;
        ss << "CLFLUSH line size in bytes: " << lineSize;
        result.push_back(ss.str());
    }
    {
        const size_t idsNumber = static_cast<size_t>(byte2);
        std::stringstream ss;
        ss << "Maximum number of addressable IDs for logical processors: " << idsNumber;
        result.push_back(ss.str());
    }
    {
        const size_t apicID = static_cast<size_t>(byte3);
        std::stringstream ss;
        ss << "Initial APIC ID: " << apicID;
        result.push_back(ss.str());
    }
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
            result.push_back(str);
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
            result.push_back(str);
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
