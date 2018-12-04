#ifdef PARSER_STRING_H
#error Already included
#else
#define PARSER_STRING_H

class ParserString
{
    public:
        ParserString();
        explicit ParserString(std::string const str, size_t value);
        explicit ParserString(std::string const str1, std::string const str2);
        ~ParserString();

        ParserString &clear();

        ParserString &prefix(std::string const &str);

        ParserString &append(size_t value);
        ParserString &append(std::string const &str);

        std::string str() const;

    private:
        std::string m_str;
};

#endif
