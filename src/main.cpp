#include <iostream>
#include <sstream>

static_assert(sizeof(size_t) == 8, "size_t expected to be 64 bit");

int main(int argc, char *argv[])
try
{
    if (argc != 3)
    {
        throw std::invalid_argument("Usage: cpuid-cli RAX RCX");
    }

    size_t RAX_value = 0;
    {
        std::stringstream ss { argv[1] };
        ss >> RAX_value;
    }

    size_t RCX_value = 0;
    {
        std::stringstream ss { argv[2] };
        ss >> RCX_value;
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
