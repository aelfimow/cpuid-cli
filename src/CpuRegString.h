#ifdef CPU_REG_STRING_H
#error Already included
#else
#define CPU_REG_STRING_H

class CpuRegString
{
    public:
        explicit CpuRegString(size_t value);
        ~CpuRegString();

        std::string str() const;

    private:
        std::string m_str;

    public:
        CpuRegString() = delete;
};

#endif
