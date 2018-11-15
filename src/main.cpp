#include <iostream>
#include <sstream>
#include <map>
#include <memory>
#include <vector>
#include <functional>

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
#include "cpuid_response.h"
#include "cpuid_func.h"

static_assert(sizeof(size_t) == 8, "size_t expected to be 64 bit");

int main(int argc, char *argv[])
try
{
    if (argc < 2)
    {
        throw std::invalid_argument("Usage: cpuid-cli RAX RCX. (hex-values expected)");
    }

    auto str2hex = [](char const *str)
    {
        size_t value = 0;
        std::stringstream ss;
        ss << std::hex << str;
        ss >> value;
        return value;
    };

    size_t RAX_value = str2hex(argc >= 2 ? argv[1] : "0");
    size_t RCX_value = str2hex(argc >= 3 ? argv[2] : "0");

    size_t output[4] = { 0, 0, 0, 0 };

    ::execute_cpuid(RAX_value, RCX_value, output);

    size_t &RAX = output[0];
    size_t &RBX = output[1];
    size_t &RCX = output[2];
    size_t &RDX = output[3];

    cpuid_response const response(RAX, RBX, RCX, RDX);

    std::cout << "{ " << std::hex << RAX_value << ", " << RCX_value << " }" << std::endl;
    std::cout << response.str() << std::endl;

    std::map<size_t, std::function<IParser *(cpuid_response const &)>> const factory
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
        { 0x0B, [](cpuid_response const &d) { return new Parser_B_0(d); } }
    };

    if (auto f = factory.find(RAX_value); f != factory.end())
    {
        std::unique_ptr<IParser> parser(f->second(response));

        auto result { parser->parse() };

        for (auto str: result)
        {
            std::cout << str << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
catch (std::exception &exc)
{
    std::cerr << "Exception: " << exc.what() << std::endl;
    return EXIT_FAILURE;
}
catch (...)
{
    std::cerr << "Error: exception" << std::endl;
    return EXIT_FAILURE;
}
