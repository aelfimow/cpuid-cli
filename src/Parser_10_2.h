#ifdef PARSER_10_2_H
#error Already included
#else
#define PARSER_10_2_H

class cpuid_response;

class Parser_10_2 : public IParser
{
    public:
        explicit Parser_10_2(cpuid_response const &data);
        ~Parser_10_2();

        parse_result_t parse() const override final;

    private:
        parse_result_t m_result;
        IParser *m_next;

        void parseRAX(size_t value);
        void parseRBX(size_t value);
        void parseRCX(size_t value);
        void parseRDX(size_t value);

    public:
        Parser_10_2() = delete;
        Parser_10_2(Parser_10_2 const &) = delete;
        Parser_10_2 &operator=(Parser_10_2 const &) = delete;
};

#endif
