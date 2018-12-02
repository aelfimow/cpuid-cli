#ifdef PARSER_EXT_8_H
#error Already included
#else
#define PARSER_EXT_8_H

class cpuid_response;

class Parser_Ext_8 : public IParser
{
    public:
        explicit Parser_Ext_8(cpuid_response const &data);
        ~Parser_Ext_8();

        parse_result_t parse() override final;

    private:
        parse_result_t m_result;

        void parseRAX(size_t value);
        void parseRBX(size_t value);
        void parseRCX(size_t value);
        void parseRDX(size_t value);

    public:
        Parser_Ext_8() = delete;
};

#endif
