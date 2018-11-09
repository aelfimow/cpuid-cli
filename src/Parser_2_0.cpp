#include <bitset>
#include <map>
#include <vector>

#include "IParser.h"
#include "Parser_2_0.h"
#include "cpuid_response.h"


Parser_2_0::Parser_2_0(cpuid_response const &data) :
    IParser { },
    result { }
{
    size_t regs[] { (data.RAX() & 0xFFFFFF00), data.RBX(), data.RCX(), data.RDX() };

    for (auto r: regs)
    {
        std::bitset<32> bits { r };

        bool isValid { (0 == bits[31]) };

        if (isValid)
        {
            auto descriptors { split(r) };
            parse(descriptors);
        }
    }
}

Parser_2_0::~Parser_2_0()
{
}

parse_result_t Parser_2_0::parse() const
{
    return result;
}

std::vector<uint8_t> Parser_2_0::split(size_t value) const
{
    const size_t mask8bit { 0x00FF };

    std::vector<uint8_t> splitResult
    {
        static_cast<uint8_t>(value & mask8bit),
        static_cast<uint8_t>((value >> 8) & mask8bit),
        static_cast<uint8_t>((value >> 16) & mask8bit),
        static_cast<uint8_t>((value >> 24) & mask8bit),
    };

    return splitResult;
}

void Parser_2_0::parse(std::vector<uint8_t> &descriptors)
{
    auto enc { descriptorsEncoding() };

    for (auto d: descriptors)
    {
        std::string str { enc[d] };

        bool isEmpty { (0 == str.length()) };

        if (!isEmpty)
        {
            result.push_back(str);
        }
    }
}

std::map<uint8_t, std::string> Parser_2_0::descriptorsEncoding() const
{
    std::map<uint8_t, std::string> enc;

    enc[0x00] = "";
    enc[0x01] = "Instruction TLB: 4 KByte pages, 4-way set associative, 32 entries";
    enc[0x02] = "Instruction TLB: 4 MByte pages, fully associative, 2 entries";
    enc[0x03] = "Data TLB: 4 KByte pages, 4-way set associative, 64 entries";
    enc[0x04] = "Data TLB: 4 MByte pages, 4-way set associative, 8 entries";
    enc[0x05] = "Data TLB1: 4 MByte pages, 4-way set associative, 32 entries";
    enc[0x06] = "1st-level instruction cache: 8 KBytes, 4-way set associative, 32 byte line size";
    enc[0x07] = "";
    enc[0x08] = "1st-level instruction cache: 16 KBytes, 4-way set associative, 32 byte line size";
    enc[0x09] = "1st-level instruction cache: 32KBytes, 4-way set associative, 64 byte line size";
    enc[0x0A] = "1st-level data cache: 8 KBytes, 2-way set associative, 32 byte line size";
    enc[0x0B] = "Instruction TLB: 4 MByte pages, 4-way set associative, 4 entries";
    enc[0x0C] = "1st-level data cache: 16 KBytes, 4-way set associative, 32 byte line size";
    enc[0x0D] = "1st-level data cache: 16 KBytes, 4-way set associative, 64 byte line size";
    enc[0x0E] = "1st-level data cache: 24 KBytes, 6-way set associative, 64 byte line size";
    enc[0x0F] = "";

    enc[0x10] = "";
    enc[0x11] = "";
    enc[0x12] = "";
    enc[0x13] = "";
    enc[0x14] = "";
    enc[0x15] = "";
    enc[0x16] = "";
    enc[0x17] = "";
    enc[0x18] = "";
    enc[0x19] = "";
    enc[0x1A] = "";
    enc[0x1B] = "";
    enc[0x1C] = "";
    enc[0x1D] = "2nd-level cache: 128 KBytes, 2-way set associative, 64 byte line size";
    enc[0x1E] = "";
    enc[0x1F] = "";

    enc[0x20] = "";
    enc[0x21] = "2nd-level cache: 256 KBytes, 8-way set associative, 64 byte line size";
    enc[0x22] = "3rd-level cache: 512 KBytes, 4-way set associative, 64 byte line size, 2 lines per sector";
    enc[0x23] = "3rd-level cache: 1 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector";
    enc[0x24] = "2nd-level cache: 1 MBytes, 16-way set associative, 64 byte line size";
    enc[0x25] = "3rd-level cache: 2 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector";
    enc[0x26] = "";
    enc[0x27] = "";
    enc[0x28] = "";
    enc[0x29] = "3rd-level cache: 4 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector";
    enc[0x2A] = "";
    enc[0x2B] = "";
    enc[0x2C] = "1st-level data cache: 32 KBytes, 8-way set associative, 64 byte line size";
    enc[0x2D] = "";
    enc[0x2E] = "";
    enc[0x2F] = "";

    enc[0x30] = "1st-level instruction cache: 32 KBytes, 8-way set associative, 64 byte line size";
    enc[0x31] = "";
    enc[0x32] = "";
    enc[0x33] = "";
    enc[0x34] = "";
    enc[0x35] = "";
    enc[0x36] = "";
    enc[0x37] = "";
    enc[0x38] = "";
    enc[0x39] = "";
    enc[0x3A] = "";
    enc[0x3B] = "";
    enc[0x3C] = "";
    enc[0x3D] = "";
    enc[0x3E] = "";
    enc[0x3F] = "";

    enc[0x40] = "No 2nd-level cache or, if processor contains a valid 2nd-level cache, no 3rd-level cache";
    enc[0x41] = "2nd-level cache: 128 KBytes, 4-way set associative, 32 byte line size";
    enc[0x42] = "2nd-level cache: 256 KBytes, 4-way set associative, 32 byte line size";
    enc[0x43] = "2nd-level cache: 512 KBytes, 4-way set associative, 32 byte line size";
    enc[0x44] = "2nd-level cache: 1 MByte, 4-way set associative, 32 byte line size";
    enc[0x45] = "2nd-level cache: 2 MByte, 4-way set associative, 32 byte line size";
    enc[0x46] = "3rd-level cache: 4 MByte, 4-way set associative, 64 byte line size";
    enc[0x47] = "3rd-level cache: 8 MByte, 8-way set associative, 64 byte line size";
    enc[0x48] = "2nd-level cache: 3MByte, 12-way set associative, 64 byte line size";
    enc[0x49] = "2nd- or 3rd-level cache: 4MB, 16-way set associative, 64-byte line size";
    enc[0x4A] = "3rd-level cache: 6MByte, 12-way set associative, 64 byte line size";
    enc[0x4B] = "3rd-level cache: 8MByte, 16-way set associative, 64 byte line size";
    enc[0x4C] = "3rd-level cache: 12MByte, 12-way set associative, 64 byte line size";
    enc[0x4D] = "3rd-level cache: 16MByte, 16-way set associative, 64 byte line size";
    enc[0x4E] = "2nd-level cache: 6MByte, 24-way set associative, 64 byte line size";
    enc[0x4F] = "Instruction TLB: 4 KByte pages, 32 entries";

    enc[0x50] = "Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 64 entries";
    enc[0x51] = "Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 128 entries";
    enc[0x52] = "Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 256 entries";
    enc[0x53] = "";
    enc[0x54] = "";
    enc[0x55] = "Instruction TLB: 2-MByte or 4-MByte pages, fully associative, 7 entries";
    enc[0x56] = "Data TLB0: 4 MByte pages, 4-way set associative, 16 entries";
    enc[0x57] = "Data TLB0: 4 KByte pages, 4-way associative, 16 entries";
    enc[0x58] = "";
    enc[0x59] = "Data TLB0: 4 KByte pages, fully associative, 16 entries";
    enc[0x5A] = "Data TLB0: 2 MByte or 4 MByte pages, 4-way set associative, 32 entries";
    enc[0x5B] = "Data TLB: 4 KByte and 4 MByte pages, 64 entries";
    enc[0x5C] = "Data TLB: 4 KByte and 4 MByte pages,128 entries";
    enc[0x5D] = "Data TLB: 4 KByte and 4 MByte pages,256 entries";
    enc[0x5E] = "";
    enc[0x5F] = "";

    enc[0x60] = "1st-level data cache: 16 KByte, 8-way set associative, 64 byte line size";
    enc[0x61] = "Instruction TLB: 4 KByte pages, fully associative, 48 entries";
    enc[0x62] = "";
    enc[0x63] = "Data TLB: 2 MByte or 4 MByte pages, 4-way set associative, 32 entries and a separate array with 1 GByte pages, 4-way set associative, 4 entries";
    enc[0x64] = "Data TLB: 4 KByte pages, 4-way set associative, 512 entries";
    enc[0x65] = "";
    enc[0x66] = "1st-level data cache: 8 KByte, 4-way set associative, 64 byte line size";
    enc[0x67] = "1st-level data cache: 16 KByte, 4-way set associative, 64 byte line size";
    enc[0x68] = "1st-level data cache: 32 KByte, 4-way set associative, 64 byte line size";
    enc[0x69] = "";
    enc[0x6A] = "uTLB: 4 KByte pages, 8-way set associative, 64 entries";
    enc[0x6B] = "DTLB: 4 KByte pages, 8-way set associative, 256 entries";
    enc[0x6C] = "DTLB: 2M/4M pages, 8-way set associative, 128 entries";
    enc[0x6D] = "DTLB: 1 GByte pages, fully associative, 16 entries";
    enc[0x6E] = "";
    enc[0x6F] = "";

    enc[0x70] = "Trace cache: 12 K-µop, 8-way set associative";
    enc[0x71] = "Trace cache: 16 K-µop, 8-way set associative";
    enc[0x72] = "Trace cache: 32 K-µop, 8-way set associative";
    enc[0x73] = "";
    enc[0x74] = "";
    enc[0x75] = "";
    enc[0x76] = "Instruction TLB: 2M/4M pages, fully associative, 8 entries";
    enc[0x77] = "";
    enc[0x78] = "2nd-level cache: 1 MByte, 4-way set associative, 64byte line size";
    enc[0x79] = "2nd-level cache: 128 KByte, 8-way set associative, 64 byte line size, 2 lines per sector";
    enc[0x7A] = "2nd-level cache: 256 KByte, 8-way set associative, 64 byte line size, 2 lines per sector";
    enc[0x7B] = "2nd-level cache: 512 KByte, 8-way set associative, 64 byte line size, 2 lines per sector";
    enc[0x7C] = "2nd-level cache: 1 MByte, 8-way set associative, 64 byte line size, 2 lines per sector";
    enc[0x7D] = "2nd-level cache: 2 MByte, 8-way set associative, 64byte line size";
    enc[0x7E] = "";
    enc[0x7F] = "2nd-level cache: 512 KByte, 2-way set associative, 64-byte line size";

    enc[0x80] = "2nd-level cache: 512 KByte, 8-way set associative, 64-byte line size";
    enc[0x81] = "";
    enc[0x82] = "2nd-level cache: 256 KByte, 8-way set associative, 32 byte line size";
    enc[0x83] = "2nd-level cache: 512 KByte, 8-way set associative, 32 byte line size";
    enc[0x84] = "2nd-level cache: 1 MByte, 8-way set associative, 32 byte line size";
    enc[0x85] = "2nd-level cache: 2 MByte, 8-way set associative, 32 byte line size";
    enc[0x86] = "2nd-level cache: 512 KByte, 4-way set associative, 64 byte line size";
    enc[0x87] = "2nd-level cache: 1 MByte, 8-way set associative, 64 byte line size";
    enc[0x88] = "";
    enc[0x89] = "";
    enc[0x8A] = "";
    enc[0x8B] = "";
    enc[0x8C] = "";
    enc[0x8D] = "";
    enc[0x8E] = "";
    enc[0x8F] = "";

    enc[0x90] = "";
    enc[0x91] = "";
    enc[0x92] = "";
    enc[0x93] = "";
    enc[0x94] = "";
    enc[0x95] = "";
    enc[0x96] = "";
    enc[0x97] = "";
    enc[0x98] = "";
    enc[0x99] = "";
    enc[0x9A] = "";
    enc[0x9B] = "";
    enc[0x9C] = "";
    enc[0x9D] = "";
    enc[0x9E] = "";
    enc[0x9F] = "";

    enc[0xA0] = "DTLB: 4k pages, fully associative, 32 entries";
    enc[0xA1] = "";
    enc[0xA2] = "";
    enc[0xA3] = "";
    enc[0xA4] = "";
    enc[0xA5] = "";
    enc[0xA6] = "";
    enc[0xA7] = "";
    enc[0xA8] = "";
    enc[0xA9] = "";
    enc[0xAA] = "";
    enc[0xAB] = "";
    enc[0xAC] = "";
    enc[0xAD] = "";
    enc[0xAE] = "";
    enc[0xAF] = "";

    enc[0xB0] = "Instruction TLB: 4 KByte pages, 4-way set associative, 128 entries";
    enc[0xB1] = "Instruction TLB: 2M pages, 4-way, 8 entries or 4M pages, 4-way, 4 entries";
    enc[0xB2] = "Instruction TLB: 4KByte pages, 4-way set associative, 64 entries";
    enc[0xB3] = "Data TLB: 4 KByte pages, 4-way set associative, 128 entries";
    enc[0xB4] = "Data TLB1: 4 KByte pages, 4-way associative, 256 entries";
    enc[0xB5] = "Instruction TLB: 4KByte pages, 8-way set associative, 64 entries";
    enc[0xB6] = "Instruction TLB: 4KByte pages, 8-way set associative, 128 entries";
    enc[0xB7] = "";
    enc[0xB8] = "";
    enc[0xB9] = "";
    enc[0xBA] = "Data TLB1: 4 KByte pages, 4-way associative, 64 entries";
    enc[0xBB] = "";
    enc[0xBC] = "";
    enc[0xBD] = "";
    enc[0xBE] = "";
    enc[0xBF] = "";

    enc[0xC0] = "Data TLB: 4 KByte and 4 MByte pages, 4-way associative, 8 entries";
    enc[0xC1] = "Shared 2nd-Level TLB: 4 KByte/2MByte pages, 8-way associative, 1024 entries";
    enc[0xC2] = "DTLB: 4 KByte/2 MByte pages, 4-way associative, 16 entries";
    enc[0xC3] = "STLB Shared 2nd-Level TLB: 4 KByte /2 MByte pages, 6-way associative, 1536 entries. Also 1GBbyte pages, 4-way, 16 entries";
    enc[0xC4] = "DTLB: 2M/4M Byte pages, 4-way associative, 32 entries";
    enc[0xC5] = "";
    enc[0xC6] = "";
    enc[0xC7] = "";
    enc[0xC8] = "";
    enc[0xC9] = "";
    enc[0xCA] = "Shared 2nd-Level TLB: 4 KByte pages, 4-way associative, 512 entries";
    enc[0xCB] = "";
    enc[0xCC] = "";
    enc[0xCD] = "";
    enc[0xCE] = "";
    enc[0xCF] = "";

    enc[0xD0] = "3rd-level cache: 512 KByte, 4-way set associative, 64 byte line size";
    enc[0xD1] = "3rd-level cache: 1 MByte, 4-way set associative, 64 byte line size";
    enc[0xD2] = "3rd-level cache: 2 MByte, 4-way set associative, 64 byte line size";
    enc[0xD3] = "";
    enc[0xD4] = "";
    enc[0xD5] = "";
    enc[0xD6] = "3rd-level cache: 1 MByte, 8-way set associative, 64 byte line size";
    enc[0xD7] = "3rd-level cache: 2 MByte, 8-way set associative, 64 byte line size";
    enc[0xD8] = "3rd-level cache: 4 MByte, 8-way set associative, 64 byte line size";
    enc[0xD9] = "";
    enc[0xDA] = "";
    enc[0xDB] = "";
    enc[0xDC] = "3rd-level cache: 1.5 MByte, 12-way set associative, 64 byte line size";
    enc[0xDD] = "3rd-level cache: 3 MByte, 12-way set associative, 64 byte line size";
    enc[0xDE] = "3rd-level cache: 6 MByte, 12-way set associative, 64 byte line size";
    enc[0xDF] = "";

    enc[0xE0] = "";
    enc[0xE1] = "";
    enc[0xE2] = "3rd-level cache: 2 MByte, 16-way set associative, 64 byte line size";
    enc[0xE3] = "3rd-level cache: 4 MByte, 16-way set associative, 64 byte line size";
    enc[0xE4] = "3rd-level cache: 8 MByte, 16-way set associative, 64 byte line size";
    enc[0xE5] = "";
    enc[0xE6] = "";
    enc[0xE7] = "";
    enc[0xE8] = "";
    enc[0xE9] = "";
    enc[0xEA] = "3rd-level cache: 12MByte, 24-way set associative, 64 byte line size";
    enc[0xEB] = "3rd-level cache: 18MByte, 24-way set associative, 64 byte line size";
    enc[0xEC] = "3rd-level cache: 24MByte, 24-way set associative, 64 byte line size";
    enc[0xED] = "";
    enc[0xEE] = "";
    enc[0xEF] = "";

    enc[0xF0] = "64-Byte prefetching";
    enc[0xF1] = "128-Byte prefetching";
    enc[0xF2] = "";
    enc[0xF3] = "";
    enc[0xF4] = "";
    enc[0xF5] = "";
    enc[0xF6] = "";
    enc[0xF7] = "";
    enc[0xF8] = "";
    enc[0xF9] = "";
    enc[0xFA] = "";
    enc[0xFB] = "";
    enc[0xFC] = "";
    enc[0xFD] = "";
    enc[0xFE] = "";
    enc[0xFF] = "";

    return enc;
}
