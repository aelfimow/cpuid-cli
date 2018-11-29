#ifdef PARSER_17_1_H
#error Already included
#else
#define PARSER_17_1_H

class cpuid_response;

class Parser_17_1 : public IParser
{
    public:
        explicit Parser_17_1(cpuid_response const &data);
        ~Parser_17_1();

        parse_result_t parse() const override final;

    private:
        parse_result_t m_result;
        IParser *m_next;

    public:
        Parser_17_1() = delete;
        Parser_17_1(Parser_17_1 const &) = delete;
        Parser_17_1 &operator=(Parser_17_1 const &) = delete;
};

#endif
