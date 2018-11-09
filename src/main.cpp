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
#include "cpuid_response.h"

static_assert(sizeof(size_t) == 8, "size_t expected to be 64 bit");

extern "C" void execute_cpuid(size_t RAX_value, size_t RCX_value, size_t *pOut);

int main(int argc, char *argv[])
try
{
    if (argc != 3)
    {
        throw std::invalid_argument("Usage: cpuid-cli RAX RCX. (hex-values expected)");
    }

    size_t RAX_value = 0;
    {
        std::stringstream ss;
        ss << std::hex << argv[1];
        ss >> RAX_value;
    }

    size_t RCX_value = 0;
    {
        std::stringstream ss;
        ss << std::hex << argv[2];
        ss >> RCX_value;
    }

    size_t output[4];
    size_t &RAX = output[0];
    size_t &RBX = output[1];
    size_t &RCX = output[2];
    size_t &RDX = output[3];

    execute_cpuid(RAX_value, RCX_value, output);

    std::cout << std::hex << RAX << ";" << RBX << ";" << RCX << ";" << RDX << std::endl;

    std::map<size_t, std::function<IParser *(cpuid_response const &)>> factory
    {
        { 0, [](cpuid_response const &d) { return new Parser_0_0(d); } },
        { 1, [](cpuid_response const &d) { return new Parser_1_0(d); } },
        { 2, [](cpuid_response const &d) { return new Parser_2_0(d); } }
    };

    if (auto f = factory.find(RAX_value); f != factory.end())
    {
        cpuid_response data(RAX, RBX, RCX, RDX);
        std::unique_ptr<IParser> parser(f->second(data));

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
