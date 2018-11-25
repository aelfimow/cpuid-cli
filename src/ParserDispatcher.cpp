#include <map>
#include <functional>

#include "ParserDispatcher.h"
#include "IParser.h"
#include "Parser_0_0.h"
#include "Parser_1_0.h"
#include "Parser_2_0.h"
#include "Parser_3_0.h"
#include "Parser_4_0.h"
#include "Parser_5_0.h"
#include "Parser_6_0.h"
#include "Parser_7_0.h"
#include "Parser_9_0.h"
#include "Parser_A_0.h"
#include "Parser_B_0.h"
#include "Parser_D_0.h"
#include "Parser_F_0.h"
#include "Parser_10_0.h"
#include "Parser_12_0.h"
#include "cpuid_response.h"


IParser *ParserDispatcher::Parser_for(cpuid_response const &rsp)
{
    static std::map<size_t, std::function<IParser *(cpuid_response const &)>> const factory
    {
        { 0x00, [](cpuid_response const &d) { return new Parser_0_0(d); } },
        { 0x01, [](cpuid_response const &d) { return new Parser_1_0(d); } },
        { 0x02, [](cpuid_response const &d) { return new Parser_2_0(d); } },
        { 0x03, [](cpuid_response const &d) { return new Parser_3_0(d); } },
        { 0x04, [](cpuid_response const &d) { return new Parser_4_0(d); } },
        { 0x05, [](cpuid_response const &d) { return new Parser_5_0(d); } },
        { 0x06, [](cpuid_response const &d) { return new Parser_6_0(d); } },
        { 0x07, [](cpuid_response const &d) { return new Parser_7_0(d); } },
        { 0x09, [](cpuid_response const &d) { return new Parser_9_0(d); } },
        { 0x0A, [](cpuid_response const &d) { return new Parser_A_0(d); } },
        { 0x0B, [](cpuid_response const &d) { return new Parser_B_0(d); } },
        { 0x0D, [](cpuid_response const &d) { return new Parser_D_0(d); } },
        { 0x0F, [](cpuid_response const &d) { return new Parser_F_0(d); } },
        { 0x10, [](cpuid_response const &d) { return new Parser_10_0(d); } },
        { 0x12, [](cpuid_response const &d) { return new Parser_12_0(d); } }
    };

    if (auto it = factory.find(rsp.RAX_Command()); it != factory.end())
    {
        return it->second(rsp);
    }

    return nullptr;
}
