//
// Created by Markian on 8/6/2025.
//

#pragma once
#include <optional>

namespace stm32 {

    template<typename T>
    class Result {
        Result(const bool successful, const char* message, const std::optional<T> result) : successful(successful), message(message), result(result) {}

    public:
        bool successful;
        const char* message;
        std::optional<T> result;

        [[nodiscard]] static Result ok(T result) { return{true, nullptr, result}; }
        [[nodiscard]] static Result fail(const char* message) { return{false, message, std::nullopt}; }

        bool operator==(const Result& other) const {
            return this->successful == other.successful && this->result == other.result;
        }

        bool operator!=(const Result& other) const {
            return this->successful != other.successful || this->result != other.result;
        }
    };

}
