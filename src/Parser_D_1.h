#ifdef PARSER_D_1_H
#error Already included
#else
#define PARSER_D_1_H

class cpuid_response;

class Parser_D_1 : public IParser
{
    public:
        explicit Parser_D_1(cpuid_response const &data);
        ~Parser_D_1();

        parse_result_t parse() const override final;

    private:
        parse_result_t m_result;
        IParser *m_next;

        void parseRAX(size_t value);
        void parseRBX(size_t value);
        void parseRCX(size_t value);
        void parseRDX(size_t value);

    public:
        Parser_D_1() = delete;
        Parser_D_1(Parser_D_1 const &) = delete;
        Parser_D_1 &operator=(Parser_D_1 const &) = delete;
};

#endif