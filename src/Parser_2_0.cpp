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
    size_t const regs[] { (data.RAX() & 0xFFFFFF00), data.RBX(), data.RCX(), data.RDX() };

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
    std::map<uint8_t, std::string> const enc
    {
        { 0x00, "" },
        { 0x01, "Instruction TLB: 4 KByte pages, 4-way set associative, 32 entries" },
        { 0x02, "Instruction TLB: 4 MByte pages, fully associative, 2 entries" },
        { 0x03, "Data TLB: 4 KByte pages, 4-way set associative, 64 entries" },
        { 0x04, "Data TLB: 4 MByte pages, 4-way set associative, 8 entries" },
        { 0x05, "Data TLB1: 4 MByte pages, 4-way set associative, 32 entries" },
        { 0x06, "1st-level instruction cache: 8 KBytes, 4-way set associative, 32 byte line size" },
        { 0x07, "" },
        { 0x08, "1st-level instruction cache: 16 KBytes, 4-way set associative, 32 byte line size" },
        { 0x09, "1st-level instruction cache: 32KBytes, 4-way set associative, 64 byte line size" },
        { 0x0A, "1st-level data cache: 8 KBytes, 2-way set associative, 32 byte line size" },
        { 0x0B, "Instruction TLB: 4 MByte pages, 4-way set associative, 4 entries" },
        { 0x0C, "1st-level data cache: 16 KBytes, 4-way set associative, 32 byte line size" },
        { 0x0D, "1st-level data cache: 16 KBytes, 4-way set associative, 64 byte line size" },
        { 0x0E, "1st-level data cache: 24 KBytes, 6-way set associative, 64 byte line size" },
        { 0x0F, "" },

        { 0x10, "" },
        { 0x11, "" },
        { 0x12, "" },
        { 0x13, "" },
        { 0x14, "" },
        { 0x15, "" },
        { 0x16, "" },
        { 0x17, "" },
        { 0x18, "" },
        { 0x19, "" },
        { 0x1A, "" },
        { 0x1B, "" },
        { 0x1C, "" },
        { 0x1D, "2nd-level cache: 128 KBytes, 2-way set associative, 64 byte line size" },
        { 0x1E, "" },
        { 0x1F, "" },

        { 0x20, "" },
        { 0x21, "2nd-level cache: 256 KBytes, 8-way set associative, 64 byte line size" },
        { 0x22, "3rd-level cache: 512 KBytes, 4-way set associative, 64 byte line size, 2 lines per sector" },
        { 0x23, "3rd-level cache: 1 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector" },
        { 0x24, "2nd-level cache: 1 MBytes, 16-way set associative, 64 byte line size" },
        { 0x25, "3rd-level cache: 2 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector" },
        { 0x26, "" },
        { 0x27, "" },
        { 0x28, "" },
        { 0x29, "3rd-level cache: 4 MBytes, 8-way set associative, 64 byte line size, 2 lines per sector" },
        { 0x2A, "" },
        { 0x2B, "" },
        { 0x2C, "1st-level data cache: 32 KBytes, 8-way set associative, 64 byte line size" },
        { 0x2D, "" },
        { 0x2E, "" },
        { 0x2F, "" },

        { 0x30, "1st-level instruction cache: 32 KBytes, 8-way set associative, 64 byte line size" },
        { 0x31, "" },
        { 0x32, "" },
        { 0x33, "" },
        { 0x34, "" },
        { 0x35, "" },
        { 0x36, "" },
        { 0x37, "" },
        { 0x38, "" },
        { 0x39, "" },
        { 0x3A, "" },
        { 0x3B, "" },
        { 0x3C, "" },
        { 0x3D, "" },
        { 0x3E, "" },
        { 0x3F, "" },

        { 0x40, "No 2nd-level cache or, if processor contains a valid 2nd-level cache, no 3rd-level cache" },
        { 0x41, "2nd-level cache: 128 KBytes, 4-way set associative, 32 byte line size" },
        { 0x42, "2nd-level cache: 256 KBytes, 4-way set associative, 32 byte line size" },
        { 0x43, "2nd-level cache: 512 KBytes, 4-way set associative, 32 byte line size" },
        { 0x44, "2nd-level cache: 1 MByte, 4-way set associative, 32 byte line size" },
        { 0x45, "2nd-level cache: 2 MByte, 4-way set associative, 32 byte line size" },
        { 0x46, "3rd-level cache: 4 MByte, 4-way set associative, 64 byte line size" },
        { 0x47, "3rd-level cache: 8 MByte, 8-way set associative, 64 byte line size" },
        { 0x48, "2nd-level cache: 3MByte, 12-way set associative, 64 byte line size" },
        { 0x49, "2nd- or 3rd-level cache: 4MB, 16-way set associative, 64-byte line size" },
        { 0x4A, "3rd-level cache: 6MByte, 12-way set associative, 64 byte line size" },
        { 0x4B, "3rd-level cache: 8MByte, 16-way set associative, 64 byte line size" },
        { 0x4C, "3rd-level cache: 12MByte, 12-way set associative, 64 byte line size" },
        { 0x4D, "3rd-level cache: 16MByte, 16-way set associative, 64 byte line size" },
        { 0x4E, "2nd-level cache: 6MByte, 24-way set associative, 64 byte line size" },
        { 0x4F, "Instruction TLB: 4 KByte pages, 32 entries" },

        { 0x50, "Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 64 entries" },
        { 0x51, "Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 128 entries" },
        { 0x52, "Instruction TLB: 4 KByte and 2-MByte or 4-MByte pages, 256 entries" },
        { 0x53, "" },
        { 0x54, "" },
        { 0x55, "Instruction TLB: 2-MByte or 4-MByte pages, fully associative, 7 entries" },
        { 0x56, "Data TLB0: 4 MByte pages, 4-way set associative, 16 entries" },
        { 0x57, "Data TLB0: 4 KByte pages, 4-way associative, 16 entries" },
        { 0x58, "" },
        { 0x59, "Data TLB0: 4 KByte pages, fully associative, 16 entries" },
        { 0x5A, "Data TLB0: 2 MByte or 4 MByte pages, 4-way set associative, 32 entries" },
        { 0x5B, "Data TLB: 4 KByte and 4 MByte pages, 64 entries" },
        { 0x5C, "Data TLB: 4 KByte and 4 MByte pages,128 entries" },
        { 0x5D, "Data TLB: 4 KByte and 4 MByte pages,256 entries" },
        { 0x5E, "" },
        { 0x5F, "" },

        { 0x60, "1st-level data cache: 16 KByte, 8-way set associative, 64 byte line size" },
        { 0x61, "Instruction TLB: 4 KByte pages, fully associative, 48 entries" },
        { 0x62, "" },
        { 0x63, "Data TLB: 2 MByte or 4 MByte pages, 4-way set associative, 32 entries and a separate array with 1 GByte pages, 4-way set associative, 4 entries" },
        { 0x64, "Data TLB: 4 KByte pages, 4-way set associative, 512 entries" },
        { 0x65, "" },
        { 0x66, "1st-level data cache: 8 KByte, 4-way set associative, 64 byte line size" },
        { 0x67, "1st-level data cache: 16 KByte, 4-way set associative, 64 byte line size" },
        { 0x68, "1st-level data cache: 32 KByte, 4-way set associative, 64 byte line size" },
        { 0x69, "" },
        { 0x6A, "uTLB: 4 KByte pages, 8-way set associative, 64 entries" },
        { 0x6B, "DTLB: 4 KByte pages, 8-way set associative, 256 entries" },
        { 0x6C, "DTLB: 2M/4M pages, 8-way set associative, 128 entries" },
        { 0x6D, "DTLB: 1 GByte pages, fully associative, 16 entries" },
        { 0x6E, "" },
        { 0x6F, "" },

        { 0x70, "Trace cache: 12 K-µop, 8-way set associative" },
        { 0x71, "Trace cache: 16 K-µop, 8-way set associative" },
        { 0x72, "Trace cache: 32 K-µop, 8-way set associative" },
        { 0x73, "" },
        { 0x74, "" },
        { 0x75, "" },
        { 0x76, "Instruction TLB: 2M/4M pages, fully associative, 8 entries" },
        { 0x77, "" },
        { 0x78, "2nd-level cache: 1 MByte, 4-way set associative, 64byte line size" },
        { 0x79, "2nd-level cache: 128 KByte, 8-way set associative, 64 byte line size, 2 lines per sector" },
        { 0x7A, "2nd-level cache: 256 KByte, 8-way set associative, 64 byte line size, 2 lines per sector" },
        { 0x7B, "2nd-level cache: 512 KByte, 8-way set associative, 64 byte line size, 2 lines per sector" },
        { 0x7C, "2nd-level cache: 1 MByte, 8-way set associative, 64 byte line size, 2 lines per sector" },
        { 0x7D, "2nd-level cache: 2 MByte, 8-way set associative, 64byte line size" },
        { 0x7E, "" },
        { 0x7F, "2nd-level cache: 512 KByte, 2-way set associative, 64-byte line size" },

        { 0x80, "2nd-level cache: 512 KByte, 8-way set associative, 64-byte line size" },
        { 0x81, "" },
        { 0x82, "2nd-level cache: 256 KByte, 8-way set associative, 32 byte line size" },
        { 0x83, "2nd-level cache: 512 KByte, 8-way set associative, 32 byte line size" },
        { 0x84, "2nd-level cache: 1 MByte, 8-way set associative, 32 byte line size" },
        { 0x85, "2nd-level cache: 2 MByte, 8-way set associative, 32 byte line size" },
        { 0x86, "2nd-level cache: 512 KByte, 4-way set associative, 64 byte line size" },
        { 0x87, "2nd-level cache: 1 MByte, 8-way set associative, 64 byte line size" },
        { 0x88, "" },
        { 0x89, "" },
        { 0x8A, "" },
        { 0x8B, "" },
        { 0x8C, "" },
        { 0x8D, "" },
        { 0x8E, "" },
        { 0x8F, "" },

        { 0x90, "" },
        { 0x91, "" },
        { 0x92, "" },
        { 0x93, "" },
        { 0x94, "" },
        { 0x95, "" },
        { 0x96, "" },
        { 0x97, "" },
        { 0x98, "" },
        { 0x99, "" },
        { 0x9A, "" },
        { 0x9B, "" },
        { 0x9C, "" },
        { 0x9D, "" },
        { 0x9E, "" },
        { 0x9F, "" },

        { 0xA0, "DTLB: 4k pages, fully associative, 32 entries" },
        { 0xA1, "" },
        { 0xA2, "" },
        { 0xA3, "" },
        { 0xA4, "" },
        { 0xA5, "" },
        { 0xA6, "" },
        { 0xA7, "" },
        { 0xA8, "" },
        { 0xA9, "" },
        { 0xAA, "" },
        { 0xAB, "" },
        { 0xAC, "" },
        { 0xAD, "" },
        { 0xAE, "" },
        { 0xAF, "" },

        { 0xB0, "Instruction TLB: 4 KByte pages, 4-way set associative, 128 entries" },
        { 0xB1, "Instruction TLB: 2M pages, 4-way, 8 entries or 4M pages, 4-way, 4 entries" },
        { 0xB2, "Instruction TLB: 4KByte pages, 4-way set associative, 64 entries" },
        { 0xB3, "Data TLB: 4 KByte pages, 4-way set associative, 128 entries" },
        { 0xB4, "Data TLB1: 4 KByte pages, 4-way associative, 256 entries" },
        { 0xB5, "Instruction TLB: 4KByte pages, 8-way set associative, 64 entries" },
        { 0xB6, "Instruction TLB: 4KByte pages, 8-way set associative, 128 entries" },
        { 0xB7, "" },
        { 0xB8, "" },
        { 0xB9, "" },
        { 0xBA, "Data TLB1: 4 KByte pages, 4-way associative, 64 entries" },
        { 0xBB, "" },
        { 0xBC, "" },
        { 0xBD, "" },
        { 0xBE, "" },
        { 0xBF, "" },

        { 0xC0, "Data TLB: 4 KByte and 4 MByte pages, 4-way associative, 8 entries" },
        { 0xC1, "Shared 2nd-Level TLB: 4 KByte/2MByte pages, 8-way associative, 1024 entries" },
        { 0xC2, "DTLB: 4 KByte/2 MByte pages, 4-way associative, 16 entries" },
        { 0xC3, "STLB Shared 2nd-Level TLB: 4 KByte /2 MByte pages, 6-way associative, 1536 entries. Also 1GBbyte pages, 4-way, 16 entries" },
        { 0xC4, "DTLB: 2M/4M Byte pages, 4-way associative, 32 entries" },
        { 0xC5, "" },
        { 0xC6, "" },
        { 0xC7, "" },
        { 0xC8, "" },
        { 0xC9, "" },
        { 0xCA, "Shared 2nd-Level TLB: 4 KByte pages, 4-way associative, 512 entries" },
        { 0xCB, "" },
        { 0xCC, "" },
        { 0xCD, "" },
        { 0xCE, "" },
        { 0xCF, "" },

        { 0xD0, "3rd-level cache: 512 KByte, 4-way set associative, 64 byte line size" },
        { 0xD1, "3rd-level cache: 1 MByte, 4-way set associative, 64 byte line size" },
        { 0xD2, "3rd-level cache: 2 MByte, 4-way set associative, 64 byte line size" },
        { 0xD3, "" },
        { 0xD4, "" },
        { 0xD5, "" },
        { 0xD6, "3rd-level cache: 1 MByte, 8-way set associative, 64 byte line size" },
        { 0xD7, "3rd-level cache: 2 MByte, 8-way set associative, 64 byte line size" },
        { 0xD8, "3rd-level cache: 4 MByte, 8-way set associative, 64 byte line size" },
        { 0xD9, "" },
        { 0xDA, "" },
        { 0xDB, "" },
        { 0xDC, "3rd-level cache: 1.5 MByte, 12-way set associative, 64 byte line size" },
        { 0xDD, "3rd-level cache: 3 MByte, 12-way set associative, 64 byte line size" },
        { 0xDE, "3rd-level cache: 6 MByte, 12-way set associative, 64 byte line size" },
        { 0xDF, "" },

        { 0xE0, "" },
        { 0xE1, "" },
        { 0xE2, "3rd-level cache: 2 MByte, 16-way set associative, 64 byte line size" },
        { 0xE3, "3rd-level cache: 4 MByte, 16-way set associative, 64 byte line size" },
        { 0xE4, "3rd-level cache: 8 MByte, 16-way set associative, 64 byte line size" },
        { 0xE5, "" },
        { 0xE6, "" },
        { 0xE7, "" },
        { 0xE8, "" },
        { 0xE9, "" },
        { 0xEA, "3rd-level cache: 12MByte, 24-way set associative, 64 byte line size" },
        { 0xEB, "3rd-level cache: 18MByte, 24-way set associative, 64 byte line size" },
        { 0xEC, "3rd-level cache: 24MByte, 24-way set associative, 64 byte line size" },
        { 0xED, "" },
        { 0xEE, "" },
        { 0xEF, "" },

        { 0xF0, "64-Byte prefetching" },
        { 0xF1, "128-Byte prefetching" },
        { 0xF2, "" },
        { 0xF3, "" },
        { 0xF4, "" },
        { 0xF5, "" },
        { 0xF6, "" },
        { 0xF7, "" },
        { 0xF8, "" },
        { 0xF9, "" },
        { 0xFA, "" },
        { 0xFB, "" },
        { 0xFC, "" },
        { 0xFD, "" },
        { 0xFE, "" },
        { 0xFF, "" }
    };

    return enc;
}
