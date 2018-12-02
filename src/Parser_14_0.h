#ifdef PARSER_14_0_H
#error Already included
#else
#define PARSER_14_0_H

class cpuid_response;

class Parser_14_0 : public IParser
{
    public:
        explicit Parser_14_0(cpuid_response const &data);
        ~Parser_14_0();

        parse_result_t parse() override final;

    private:
        parse_result_t m_result;
        IParser *m_next;

        void parseRAX(size_t value);
        void parseRBX(size_t value);
        void parseRCX(size_t value);
        void parseRDX(size_t value);

    public:
        Parser_14_0() = delete;
        Parser_14_0(Parser_14_0 const &) = delete;
        Parser_14_0 &operator=(Parser_14_0 const &) = delete;
};

#endif
