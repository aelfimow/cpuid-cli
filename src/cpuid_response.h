#ifdef CPUID_RESPONSE_H
#error Already included
#else
#define CPUID_RESPONSE_H

class cpuid_response
{
    public:
        explicit cpuid_response(size_t RAX, size_t RBX, size_t RCX, size_t RDX);
        ~cpuid_response();

        size_t RAX() const;
        size_t RBX() const;
        size_t RCX() const;
        size_t RDX() const;

        std::string str() const;

    private:
        size_t const m_RAX;
        size_t const m_RBX;
        size_t const m_RCX;
        size_t const m_RDX;

    public:
        cpuid_response() = delete;
        cpuid_response(const cpuid_response &instance) = delete;
        cpuid_response(const cpuid_response &&instance) = delete;
        cpuid_response &operator=(const cpuid_response &instance) = delete;
        cpuid_response &operator=(const cpuid_response &&instance) = delete;
};

#endif
