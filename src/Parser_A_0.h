#ifdef PARSER_A_0_H
#error Already included
#else
#define PARSER_A_0_H

class cpuid_response;

class Parser_A_0 : public IParser
{
    public:
        explicit Parser_A_0(cpuid_response const &data);
        ~Parser_A_0();

        parse_result_t parse() override final;

    private:
        parse_result_t result;

        void parseRAX(size_t value);
        void parseRBX(size_t value);
        void parseRCX(size_t value);
        void parseRDX(size_t value);

    public:
        Parser_A_0() = delete;
};

#endif
