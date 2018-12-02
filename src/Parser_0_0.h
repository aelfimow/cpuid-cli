#ifdef PARSER_0_0_H
#error Already included
#else
#define PARSER_0_0_H

class cpuid_response;

class Parser_0_0 : public IParser
{
    public:
        explicit Parser_0_0(cpuid_response const &data);
        ~Parser_0_0();

        parse_result_t parse() override final;

    private:
        size_t maxInputValue;
        std::string vendorStr;

    public:
        Parser_0_0() = delete;
};

#endif
