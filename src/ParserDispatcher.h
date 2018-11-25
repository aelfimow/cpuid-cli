#ifdef PARSER_DISPATCHER_H
#error Already included
#else
#define PARSER_DISPATCHER_H

class IParser;
class cpuid_response;

class ParserDispatcher
{
    public:
        static IParser *Parser_for(cpuid_response const &rsp);

    public:
        ParserDispatcher() = delete;
        ParserDispatcher(ParserDispatcher const &inst) = delete;
        ~ParserDispatcher() = delete;
};

#endif
