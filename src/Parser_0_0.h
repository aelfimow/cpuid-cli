#ifdef PARSER_0_0_H
#error Already included
#else
#define PARSER_0_0_H

#include <string>
#include <list>

class Parser_0_0
{
    public:
        Parser_0_0(size_t RAX, size_t RBX, size_t RCX, size_t RDX);
        ~Parser_0_0();

        std::list<std::string> get() const;

    private:
        size_t maxInputValue;
        std::string vendorStr;

    public:
        Parser_0_0() = delete;
};

#endif
