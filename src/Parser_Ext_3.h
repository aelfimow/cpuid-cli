#ifdef PARSER_EXT_3_H
#error Already included
#else
#define PARSER_EXT_3_H

class cpuid_response;

class Parser_Ext_3 : public IParser
{
    public:
        explicit Parser_Ext_3(cpuid_response const &data);
        ~Parser_Ext_3();

        parse_result_t parse() const override final;

    private:
        parse_result_t m_result;

    public:
        Parser_Ext_3() = delete;
};

#endif
