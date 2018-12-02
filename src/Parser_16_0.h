#ifdef PARSER_16_0_H
#error Already included
#else
#define PARSER_16_0_H

class cpuid_response;

class Parser_16_0 : public IParser
{
    public:
        explicit Parser_16_0(cpuid_response const &data);
        ~Parser_16_0();

        parse_result_t parse() override final;

    private:
        parse_result_t m_result;

        void parseRAX(size_t value);
        void parseRBX(size_t value);
        void parseRCX(size_t value);
        void parseRDX(size_t value);

    public:
        Parser_16_0() = delete;
};

#endif
