//
// Created by Markian on 8/6/2025.
//

#include "../../Inc/stm/Result.h"

namespace stm32 {

    Result Result::ok() {
        return Result{true};
    }

    Result Result::fail(const char *message) {
        return Result{false, message};
    }

    bool Result::operator==(const Result &other) const {
        return this->successful == other.successful;
    }

    bool Result::operator!=(const Result &other) const {
        return this->successful != other.successful;
    }

}