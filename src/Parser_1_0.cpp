#include <sstream>
#include <bitset>

#include "Parser_1_0.h"


Parser_1_0::Parser_1_0(size_t RAX, size_t RBX, size_t RCX, size_t RDX) :
    result {}
{
    parseRAX(RAX);
    parseRBX(RBX);
    parseRCX(RCX);
    parseRDX(RDX);
}

Parser_1_0::~Parser_1_0()
{
}

std::list<std::string> Parser_1_0::get() const
{
    return result;
}

void Parser_1_0::parseRAX(size_t value)
{
    value = value;
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
    std::map<size_t, std::string> featureStr;

    featureStr[0] = "SSE3 extensions";
    featureStr[1] = "Carryless multiplication (PCLMULQDQ)";
    featureStr[2] = "64-bit DS area (DTES64)";
    featureStr[3] = "MONITOR/MWAIT";
    featureStr[4] = "CPL Qualified Debug Store (DS-CPL)";
    featureStr[5] = "Virtual Machine Extensions (VMX)";
    featureStr[6] = "Safer Mode Extensions (SMX)";
    featureStr[7] = "Enhanced Intel SpeedStep(R) Technology";
    featureStr[8] = "Thermal Monitor 2 (TM2)";
    featureStr[9] = "SSSE3 Extensions";
    featureStr[10] = "L1 Context ID (CNXT-ID)";
    featureStr[11] = "SDBG";
    featureStr[12] = "Fused Multiply Add (FMA)";
    featureStr[13] = "CMPXCHG16B";
    featureStr[14] = "xTPR Update Control";
    featureStr[15] = "Perf/Debug Capability MSR (PDCM)";

    featureStr[17] = "Process-context Identifiers (PCID)";
    featureStr[18] = "Direct Cache Access (DCA)";
    featureStr[19] = "SSE4.1";
    featureStr[20] = "SSE4.2";
    featureStr[21] = "x2APIC";
    featureStr[22] = "MOVBE";
    featureStr[23] = "POPCNT";
    featureStr[24] = "TSC-Deadline";
    featureStr[25] = "AES";
    featureStr[26] = "XSAVE";
    featureStr[27] = "OSXSAVE";
    featureStr[28] = "AVX";
    featureStr[29] = "F16C";
    featureStr[30] = "RDRAND";

    return featureStr;
}

std::map<size_t, std::string> Parser_1_0::featuresRDX() const
{
    std::map<size_t, std::string> featureStr;

    featureStr[0] = "x87 FPU on Chip";
    featureStr[1] = "Virtual-8086 Mode Enhancement (VME)";
    featureStr[2] = "Debugging Extensions (DE)";
    featureStr[3] = "Page Size Extensions (PSE)";
    featureStr[4] = "Time Stamp Counter (TSC)";
    featureStr[5] = "RDMSR and WRMSR Support (MSR)";
    featureStr[6] = "Physical Address Extensions (PAE)";
    featureStr[7] = "Machine Check Exception (MCE)";
    featureStr[8] = "CMPXCHG8B Instruction (CX8)";
    featureStr[9] = "APIC on Chip (APIC)";

    featureStr[11] = "SYSENTER and SYSEXIT (SEP)";
    featureStr[12] = "Memory Type Range Registers (MTRR)";
    featureStr[13] = "PTE Global Bit (PGE)";
    featureStr[14] = "Machine Check Architecture (MCA)";
    featureStr[15] = "Conditional Move/Compare Instruction (CMOV)";
    featureStr[16] = "Page Attribute Table (PAT)";
    featureStr[17] = "Page Size Extension (PSE-36)";
    featureStr[18] = "Processor Serial Number (PSN)";
    featureStr[19] = "CLFLUSH instruction (CLFSH)";

    featureStr[21] = "Debug Store (DS)";
    featureStr[22] = "Thermal Monitor and Clock Ctrl (ACPI)";
    featureStr[23] = "MMX Technology";
    featureStr[24] = "FXSAVE/FXRSTOR (FXSR)";
    featureStr[25] = "SSE Extensions";
    featureStr[26] = "SSE2 Extensions";
    featureStr[27] = "Self Snoop (SS)";
    featureStr[28] = "Multi-threading (HTT)";
    featureStr[29] = "Thermal Monitor (TM)";

    featureStr[31] = "Pend. Brk. EN. (PBE)";

    return featureStr;
}
