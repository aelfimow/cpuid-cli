#include <cstdint>
#include "cpuid_response.h"

cpuid_response::cpuid_response(size_t RAX, size_t RBX, size_t RCX, size_t RDX) :
    m_RAX { RAX },
    m_RBX { RBX },
    m_RCX { RCX },
    m_RDX { RDX }
{
}

cpuid_response::~cpuid_response()
{
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
