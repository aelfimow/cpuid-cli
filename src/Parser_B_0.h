#ifdef PARSER_B_0_H
#error Already included
#else
#define PARSER_B_0_H

class cpuid_response;

class Parser_B_0 : public IParser
{
    public:
        explicit Parser_B_0(cpuid_response const &data);
        ~Parser_B_0();

        parse_result_t parse() const override final;

    private:
        parse_result_t result;
        bool sub_leaf_valid;
        size_t shift_value;

        void parseRAX(size_t value);
        void parseRBX(size_t value);
        void parseRCX(size_t value);
        void parseRDX(size_t value);

    public:
        Parser_B_0() = delete;
};

#endif
