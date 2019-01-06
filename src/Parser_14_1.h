#ifdef PARSER_14_1_H
#error Already included
#else
#define PARSER_14_1_H

class cpuid_response;

class Parser_14_1 : public IParser
{
    public:
        explicit Parser_14_1(cpuid_response const &data);
        ~Parser_14_1();

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
        Parser_14_1() = delete;
        Parser_14_1(Parser_14_1 const &) = delete;
        Parser_14_1 &operator=(Parser_14_1 const &) = delete;
};

#endif
