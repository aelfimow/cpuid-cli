#ifdef PARSER_15_0_H
#error Already included
#else
#define PARSER_15_0_H

class cpuid_response;

class Parser_15_0 : public IParser
{
    public:
        explicit Parser_15_0(cpuid_response const &data);
        ~Parser_15_0();

        parse_result_t parse() const override final;

    private:
        parse_result_t m_result;

        void parseRAX(size_t value);
        void parseRBX(size_t value);
        void parseRCX(size_t value);
        void parseRDX(size_t value);

    public:
        Parser_15_0() = delete;
};

#endif
