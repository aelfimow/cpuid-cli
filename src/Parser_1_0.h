#ifdef PARSER_1_0_H
#error Already included
#else
#define PARSER_1_0_H

class cpuid_response;

class Parser_1_0 : public IParser
{
    public:
        explicit Parser_1_0(cpuid_response const &data);
        ~Parser_1_0();

        parse_result_t parse() override final;

    private:
        void parseRAX(size_t value);
        void parseRBX(size_t value);
        void parseRCX(size_t value);
        void parseRDX(size_t value);

        std::map<size_t, std::string> featuresRCX() const;
        std::map<size_t, std::string> featuresRDX() const;

    private:
        size_t const m_RAX;
        size_t const m_RBX;
        size_t const m_RCX;
        size_t const m_RDX;

        parse_result_t m_result;

    public:
        Parser_1_0() = delete;
};

#endif
