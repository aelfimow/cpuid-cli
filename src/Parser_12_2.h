#ifdef PARSER_12_2_H
#error Already included
#else
#define PARSER_12_2_H

class cpuid_response;

class Parser_12_2 : public IParser
{
    public:
        explicit Parser_12_2(cpuid_response const &data);
        ~Parser_12_2();

        parse_result_t parse() override final;

    private:
        size_t const m_RAX;
        size_t const m_RBX;
        size_t const m_RCX;
        size_t const m_RDX;

        parse_result_t m_result;
        bool const m_response_ok;

    public:
        Parser_12_2() = delete;
        Parser_12_2(Parser_12_2 const &) = delete;
        Parser_12_2 &operator=(Parser_12_2 const &) = delete;
};

#endif
