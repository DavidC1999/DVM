#pragma once

#include <cstdint>

#include "Token.h"


class NumberToken : public Token {
public:
    static const uint16_t TYPE_ID = __COUNTER__;
    SET_DEBUG_NAME(NUMBER)

    NumberToken(uint64_t num, uint64_t line) :
        Token(TYPE_ID, line), m_num(num) {}

    std::unique_ptr<Token> clone() override {
        return std::make_unique<NumberToken>(m_num, m_line);
    }

    [[nodiscard]] uint64_t get_num() const {
        return m_num;
    }
private:
    uint64_t m_num;
};