#ifdef PARSER_EXT_4_H
#error Already included
#else
#define PARSER_EXT_4_H

class cpuid_response;

class Parser_Ext_4 : public IParser
{
    public:
        explicit Parser_Ext_4(cpuid_response const &data);
        ~Parser_Ext_4();

        parse_result_t parse() override final;

    private:
        size_t const m_RAX;
        size_t const m_RBX;
        size_t const m_RCX;
        size_t const m_RDX;

        parse_result_t m_result;

    public:
        Parser_Ext_4() = delete;
};

#endif
