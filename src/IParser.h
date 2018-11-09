#ifdef IPARSER_H
#error Already included
#else
#define IPARSER_H

#include <string>
#include <list>

using parse_result_t = std::list<std::string>;

class IParser
{
    public:
        IParser()
        {
        }

        virtual ~IParser()
        {
        }

        virtual parse_result_t parse() const = 0;
};

#endif
