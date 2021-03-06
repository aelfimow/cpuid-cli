#ifdef BIT_EXTRACTOR_H
#error Already included
#else
#define BIT_EXTRACTOR_H

#include <utility>

class bit_extractor
{
    public:
        explicit bit_extractor(size_t value);
        ~bit_extractor();

        bool extract(size_t pos) const;

        size_t extract(size_t from, size_t to) const;

        size_t extract(std::pair<size_t, size_t> const &range) const;

    private:
        size_t const m_value;

    public:
        bit_extractor() = delete;
};

#endif
