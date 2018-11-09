#ifdef PARSER_2_0_H
#error Already included
#else
#define PARSER_2_0_H

#include <vector>
#include <map>

class Parser_2_0 : public IParser
{
    public:
        Parser_2_0(size_t RAX, size_t RBX, size_t RCX, size_t RDX);
        ~Parser_2_0();

        parse_result_t parse() const override final;

    private:
        parse_result_t result;

    private:
        std::vector<uint8_t> split(size_t value) const;
        void parse(std::vector<uint8_t> &descriptors);
        std::map<uint8_t, std::string> descriptorsEncoding() const;

    public:
        Parser_2_0() = delete;
};

#endif