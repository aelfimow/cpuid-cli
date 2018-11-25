#ifdef PARSER_12_1_H
#error Already included
#else
#define PARSER_12_1_H

class cpuid_response;

class Parser_12_1 : public IParser
{
    public:
        explicit Parser_12_1(cpuid_response const &data);
        ~Parser_12_1();

        parse_result_t parse() const override final;

    private:
        parse_result_t m_result;
        IParser *m_next;

        void parseRAX(size_t value);
        void parseRBX(size_t value);
        void parseRCX(size_t value);
        void parseRDX(size_t value);

    public:
        Parser_12_1() = delete;
        Parser_12_1(Parser_12_1 const &) = delete;
        Parser_12_1 &operator=(Parser_12_1 const &) = delete;
};

#endif
