#include <iostream>
#include <sstream>

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

    execute_cpuid(RAX_value, RCX_value, output);

    std::cout << std::hex << output[0] << ";" << output[1] << ";" << output[2] << ";" << output[3] << std::endl;

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
