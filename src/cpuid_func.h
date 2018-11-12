#ifdef CPUID_FUNC_H
#error Already included
#else
#define CPUID_FUNC_H

extern "C" void execute_cpuid(size_t RAX_value, size_t RCX_value, size_t *pOut);

#endif
