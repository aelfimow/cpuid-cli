#ifdef PARSER_0_0_H
#error Already included
#else
#define PARSER_0_0_H

class cpuid_response;

class Parser_0_0 : public IParser
{
    public:
        explicit Parser_0_0(cpuid_response const &data);
        ~Parser_0_0();

        parse_result_t parse() override final;

    private:
        size_t const m_RAX;
        size_t const m_RBX;
        size_t const m_RCX;
        size_t const m_RDX;

        parse_result_t m_result;

    public:
        Parser_0_0() = delete;
};

#endif
