#include <bitset>
#include <utility>

#include "bit_extractor.h"


bit_extractor::bit_extractor(size_t value) :
    m_value { value }
{
}

bit_extractor::~bit_extractor()
{
}

bool bit_extractor::extract(size_t pos) const
{
    std::bitset<64> value { m_value };

    return value[pos];
}

size_t bit_extractor::extract(size_t from, size_t to) const
{
    std::bitset<64> result { 0 };
    std::bitset<64> value { m_value };

    if (from < to)
    {
        std::swap(from, to);
    }

    size_t pos = 0;
    size_t const end_pos = from - to + 1;
    size_t const offset = to;

    while (pos < end_pos)
    {
        result[pos] = value[pos + offset];
        ++pos;
    }

    return result.to_ullong();
}
