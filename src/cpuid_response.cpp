#include <sstream>
#include <cstdint>

#include "cpuid_response.h"


cpuid_response::cpuid_response(size_t RAX, size_t RBX, size_t RCX, size_t RDX) :
    m_RAX_Command { 0 },
    m_RCX_Command { 0 },
    m_RAX { RAX },
    m_RBX { RBX },
    m_RCX { RCX },
    m_RDX { RDX }
{
}

cpuid_response::~cpuid_response()
{
}

void cpuid_response::command(size_t RAX, size_t RCX)
{
    m_RAX_Command = RAX;
    m_RCX_Command = RCX;
}

size_t cpuid_response::RAX_Command() const
{
    return m_RAX_Command;
}

size_t cpuid_response::RCX_Command() const
{
    return m_RCX_Command;
}

size_t cpuid_response::RAX() const
{
    return m_RAX;
}

size_t cpuid_response::RBX() const
{
    return m_RBX;
}

size_t cpuid_response::RCX() const
{
    return m_RCX;
}

size_t cpuid_response::RDX() const
{
    return m_RDX;
}

std::string cpuid_response::str() const
{
    std::stringstream ss;
    ss << "{ " << std::hex << m_RAX_Command << ", " << m_RCX_Command << " }: ";
    ss << "{ ";
    ss << std::hex << m_RAX << ";" << m_RBX << ";" << m_RCX << ";" << m_RDX;
    ss << " }";
    return ss.str();
}
