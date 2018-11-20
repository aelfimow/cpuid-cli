#ifdef PARSER_STRING_H
#error Already included
#else
#define PARSER_STRING_H

class ParserString
{
    public:
        explicit ParserString(std::string const str, size_t value);
        explicit ParserString(std::string const str1, std::string const str2);
        ~ParserString();

        std::string str() const;

    private:
        std::string m_str;

    public:
        ParserString() = delete;
};

#endif
