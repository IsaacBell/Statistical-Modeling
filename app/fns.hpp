#include "./constants.hpp"

template <class TPF_INT>
constexpr std::size_t hash_combine(std::size_t seed, TPF_INT v) noexcept
{
    return seed ^ ((static_cast<std::size_t>(v) + std::size_t{0x9e3779b9}) + (seed << std::size_t{6}) + (seed >> std::size_t{2}));
}

