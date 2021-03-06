#ifdef PARSER_10_3_H
#error Already included
#else
#define PARSER_10_3_H

class cpuid_response;

class Parser_10_3 : public IParser
{
    public:
        explicit Parser_10_3(cpuid_response const &data);
        ~Parser_10_3();

        parse_result_t parse() override final;

    private:
        size_t const m_RAX;
        size_t const m_RBX;
        size_t const m_RCX;
        size_t const m_RDX;

        parse_result_t m_result;

        bool const m_response_ok;

        void parseRAX(size_t value);
        void parseRBX(size_t value);
        void parseRCX(size_t value);
        void parseRDX(size_t value);

    public:
        Parser_10_3() = delete;
        Parser_10_3(Parser_10_3 const &) = delete;
        Parser_10_3 &operator=(Parser_10_3 const &) = delete;
};

#endif
