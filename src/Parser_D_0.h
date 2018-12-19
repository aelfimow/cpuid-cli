#ifdef PARSER_D_0_H
#error Already included
#else
#define PARSER_D_0_H

class cpuid_response;

class Parser_D_0 : public IParser
{
    public:
        explicit Parser_D_0(cpuid_response const &data);
        ~Parser_D_0();

        parse_result_t parse() override final;

    private:
        size_t const m_RAX;
        size_t const m_RBX;
        size_t const m_RCX;
        size_t const m_RDX;

        parse_result_t m_result;
        IParser * const m_next;

        void parseRAX(size_t value);
        void parseRBX(size_t value);
        void parseRCX(size_t value);
        void parseRDX(size_t value);

    public:
        Parser_D_0() = delete;
        Parser_D_0(Parser_D_0 const &) = delete;
        Parser_D_0 &operator=(Parser_D_0 const &) = delete;
};

#endif
