//
// Created by Markian on 8/8/2025.
//

#pragma once

/**
 * Extracts bits from a variable
 *
 * @param var The variable from which to extract bits
 * @param pos Where the bits to extract start
 * @param mask The mask to extract bits. Can be used with MASK<N> to extract N bits
 * @return The extracted bits
 */
template<typename T, typename M>
constexpr auto EXTRACT_BITS(T var, unsigned char pos, M mask) noexcept {
    return (var & (mask << pos)) >> pos;
}

/**
 * Returns a mask for N bits.
 *
 * @tparam N The number of bits to mask
 */
template<unsigned int N>
constexpr auto MASK = (N >= 32)
    ? 0xFFFFFFFFu
    : (1u << N) - 1u;