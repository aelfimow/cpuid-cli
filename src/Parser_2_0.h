#ifdef PARSER_2_0_H
#error Already included
#else
#define PARSER_2_0_H

class cpuid_response;

class Parser_2_0 : public IParser
{
    public:
        explicit Parser_2_0(cpuid_response const &data);
        ~Parser_2_0();

        parse_result_t parse() override final;

    private:
        size_t const m_RAX;
        size_t const m_RBX;
        size_t const m_RCX;
        size_t const m_RDX;

        parse_result_t m_result;

    private:
        std::vector<uint8_t> split(size_t value) const;
        void parse(std::vector<uint8_t> &descriptors);
        std::map<uint8_t, std::string> descriptorsEncoding() const;

    public:
        Parser_2_0() = delete;
};

#endif
