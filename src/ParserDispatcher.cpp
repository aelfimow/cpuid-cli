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
#include "Parser_14_0.h"
#include "Parser_15_0.h"
#include "Parser_16_0.h"
#include "Parser_17_0.h"
#include "Parser_Ext_0.h"
#include "Parser_Ext_1.h"
#include "Parser_Ext_2.h"
#include "Parser_Ext_3.h"
#include "Parser_Ext_4.h"
#include "Parser_Ext_6.h"
#include "Parser_Ext_7.h"
#include "Parser_Ext_8.h"
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
        { 0x12, [](cpuid_response const &d) { return new Parser_12_0(d); } },
        { 0x14, [](cpuid_response const &d) { return new Parser_14_0(d); } },
        { 0x15, [](cpuid_response const &d) { return new Parser_15_0(d); } },
        { 0x16, [](cpuid_response const &d) { return new Parser_16_0(d); } },
        { 0x17, [](cpuid_response const &d) { return new Parser_17_0(d); } },
        { 0x80000000, [](cpuid_response const &d) { return new Parser_Ext_0(d); } },
        { 0x80000001, [](cpuid_response const &d) { return new Parser_Ext_1(d); } },
        { 0x80000002, [](cpuid_response const &d) { return new Parser_Ext_2(d); } },
        { 0x80000003, [](cpuid_response const &d) { return new Parser_Ext_3(d); } },
        { 0x80000004, [](cpuid_response const &d) { return new Parser_Ext_4(d); } },
        { 0x80000006, [](cpuid_response const &d) { return new Parser_Ext_6(d); } },
        { 0x80000007, [](cpuid_response const &d) { return new Parser_Ext_7(d); } },
        { 0x80000008, [](cpuid_response const &d) { return new Parser_Ext_8(d); } }
    };

    if (auto it = factory.find(rsp.RAX_Command()); it != factory.end())
    {
        return it->second(rsp);
    }

    return nullptr;
}
