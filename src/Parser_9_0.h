#ifdef PARSER_9_0_H
#error Already included
#else
#define PARSER_9_0_H

class cpuid_response;

class Parser_9_0 : public IParser
{
    public:
        explicit PParser_9_0(cpuid_response const &data);
        ~Parser_9_0();

        parse_result_t parse() const override final;

    private:
        parse_result_t result;

        void parseRAX(size_t value);
        void parseRBX(size_t value);
        void parseRCX(size_t value);
        void parseRDX(size_t value);

    public:
        Parser_9_0() = delete;
};

#endif
