//
// Created by Markian on 8/6/2025.
//

#pragma once

namespace stm32 {

    class Result {
        explicit Result(const bool successful, const char* message = nullptr) : successful(successful), message(message) {}

    public:
        bool successful = false;
        const char* message = nullptr;

        [[nodiscard]] static Result ok();
        [[nodiscard]] static Result fail(const char* message);

        bool operator==(const Result& other) const;
        bool operator!=(const Result& other) const;
    };

}