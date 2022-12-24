#include <cstdio>

#include "./constants.hpp"

template <typename INTEGER_TYPE = int>
constexpr std::size_t hash_combine(std::size_t seed, INTEGER_TYPE v) noexcept
{
    return seed ^ ((static_cast<std::size_t>(v) + std::size_t{0x9e3779b9}) + (seed << std::size_t{6}) + (seed >> std::size_t{2}));
}

