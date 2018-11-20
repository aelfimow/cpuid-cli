#include <sstream>

#include "ParserString.h"


ParserString::ParserString(std::string const str, size_t value) :
    m_str { }
{
    std::stringstream ss;
    ss << str << ": " << value;
    m_str.append(ss.str());
}

ParserString::ParserString(std::string const str1, std::string const str2) :
    m_str { }
{
    std::stringstream ss;
    ss << str1 << ": " << str2;
    m_str.append(ss.str());
}

ParserString::~ParserString()
{
}

std::string ParserString::str() const
{
    return m_str;
}
