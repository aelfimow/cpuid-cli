#ifdef PARSER_F_0_H
#error Already included
#else
#define PARSER_F_0_H

class cpuid_response;

class Parser_F_0 : public IParser
{
    public:
        explicit Parser_F_0(cpuid_response const &data);
        ~Parser_F_0();

        parse_result_t parse() override final;

    private:
        size_t const m_RAX;
        size_t const m_RBX;
        size_t const m_RCX;
        size_t const m_RDX;

        parse_result_t m_result;
        IParser *m_next;

        void parseRAX(size_t value);
        void parseRBX(size_t value);
        void parseRCX(size_t value);
        void parseRDX(size_t value);

    public:
        Parser_F_0() = delete;
        Parser_F_0(Parser_F_0 const &) = delete;
        Parser_F_0 &operator=(Parser_F_0 const &) = delete;
};

#endif
