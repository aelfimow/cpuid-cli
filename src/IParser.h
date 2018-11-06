#ifdef IPARSER_H
#error Already included
#else
#define IPARSER_H

#include <string>
#include <list>

using ParseResult_t = std::list<std::string>;

class IParser
{
    public:
        IParser()
        {
        }

        virtual ~IParser()
        {
        }

        virtual ParseResult_t parse() const = 0;
};

#endif
