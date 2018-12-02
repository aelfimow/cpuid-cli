#ifdef PARSER_EXT_6_H
#error Already included
#else
#define PARSER_EXT_6_H

class cpuid_response;

class Parser_Ext_6 : public IParser
{
    public:
        explicit Parser_Ext_6(cpuid_response const &data);
        ~Parser_Ext_6();

        parse_result_t parse() override final;

    private:
        parse_result_t m_result;

        void parseRAX(size_t value);
        void parseRBX(size_t value);
        void parseRCX(size_t value);
        void parseRDX(size_t value);

    public:
        Parser_Ext_6() = delete;
};

#endif
