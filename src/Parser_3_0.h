#ifdef PARSER_3_0_H
#error Already included
#else
#define PARSER_3_0_H

class cpuid_response;

class Parser_3_0 : public IParser
{
    public:
        explicit Parser_3_0(cpuid_response const &data);
        ~Parser_3_0();

        parse_result_t parse() override final;

    private:
        size_t const m_RAX;
        size_t const m_RBX;
        size_t const m_RCX;
        size_t const m_RDX;

        parse_result_t m_result;

    public:
        Parser_3_0() = delete;
};

#endif
