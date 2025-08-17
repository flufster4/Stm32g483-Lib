//
// Created by Markian on 8/8/2025.
//

#pragma once

template<unsigned int N>
constexpr auto MASK = (N >= 32)
    ? 0xFFFFFFFFu
    : (1u << N) - 1u;