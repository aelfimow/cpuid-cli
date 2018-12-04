#include <sstream>

#include "ParserString.h"


ParserString::ParserString() :
    m_str { }
{
}

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

ParserString &ParserString::clear()
{
    m_str.clear();
    return *this;
}

ParserString &ParserString::prefix(std::string const &str)
{
    m_str = str;
    m_str.append(": ");
    return *this;
}

ParserString &ParserString::append(size_t value)
{
    std::stringstream ss;
    ss << value;
    m_str.append(ss.str());
    return *this;
}

ParserString &ParserString::append(std::string const &str)
{
    m_str.append(str);
    return *this;
}

std::string ParserString::str() const
{
    return m_str;
}
