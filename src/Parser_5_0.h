#ifdef PARSER_5_0_H
#error Already included
#else
#define PARSER_5_0_H

class cpuid_response;

class Parser_5_0 : public IParser
{
    public:
        explicit Parser_5_0(cpuid_response const &data);
        ~Parser_5_0();

        parse_result_t parse() override final;

    private:
        size_t const m_RAX;
        size_t const m_RBX;
        size_t const m_RCX;
        size_t const m_RDX;

        parse_result_t m_result;

        void parseRAX(size_t value);
        void parseRBX(size_t value);
        void parseRCX(size_t value);
        void parseRDX(size_t value);

    public:
        Parser_5_0() = delete;
};

#endif
