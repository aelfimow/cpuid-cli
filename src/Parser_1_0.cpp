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
    value = value;
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
    value = value;
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
