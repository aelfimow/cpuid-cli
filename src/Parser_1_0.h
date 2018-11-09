#ifdef PARSER_1_0_H
#error Already included
#else
#define PARSER_1_0_H

#include <map>

class Parser_1_0 : public IParser
{
    public:
        Parser_1_0(size_t RAX, size_t RBX, size_t RCX, size_t RDX);
        ~Parser_1_0();

        parse_result_t parse() const override final;

    private:
        void parseRAX(size_t value);
        void parseRBX(size_t value);
        void parseRCX(size_t value);
        void parseRDX(size_t value);

        std::map<size_t, std::string> featuresRCX() const;
        std::map<size_t, std::string> featuresRDX() const;

    private:
        parse_result_t result;

    public:
        Parser_1_0() = delete;
};

#endif
