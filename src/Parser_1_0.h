#ifdef PARSER_1_0_H
#error Already included
#else
#define PARSER_1_0_H

#include <string>
#include <list>
#include <map>

class Parser_1_0
{
    public:
        Parser_1_0(size_t RAX, size_t RBX, size_t RCX, size_t RDX);
        ~Parser_1_0();

        std::list<std::string> get() const;

    private:
        void parseRAX(size_t value);
        void parseRBX(size_t value);
        void parseRCX(size_t value);
        void parseRDX(size_t value);

        std::map<size_t, std::string> featuresRCX() const;
        std::map<size_t, std::string> featuresRDX() const;

    private:
        std::list<std::string> result;

    public:
        Parser_1_0() = delete;
};

#endif
