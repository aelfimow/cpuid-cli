#include <iostream>
#include <sstream>
#include <map>
#include <memory>
#include <vector>

#include "ParserDispatcher.h"
#include "IParser.h"
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

    size_t const RAX_value = argc >= 2 ? str2hex(argv[1]) : 0;
    size_t const RCX_value = argc >= 3 ? str2hex(argv[2]) : 0;

    size_t output[4] = { 0, 0, 0, 0 };

    ::execute_cpuid(RAX_value, RCX_value, output);

    size_t &RAX = output[0];
    size_t &RBX = output[1];
    size_t &RCX = output[2];
    size_t &RDX = output[3];

    cpuid_response response(RAX, RBX, RCX, RDX);
    response.command(RAX_value, RCX_value);

    std::cout << response.str() << std::endl;

    std::unique_ptr<IParser> parser(ParserDispatcher::Parser_for(response));

    if (!parser)
    {
        throw std::invalid_argument("No parser.");
    }

    auto result { parser->parse() };

    for (auto str: result)
    {
        std::cout << str << std::endl;
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
