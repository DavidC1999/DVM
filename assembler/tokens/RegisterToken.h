#pragma once

#include <cstdint>

#include "Token.h"


class RegisterToken : public Token {
public:
    static const uint16_t TYPE_ID = __COUNTER__;
    SET_DEBUG_NAME(REGISTER)
    RegisterToken(uint64_t reg, uint64_t line) :
        Token(TYPE_ID, line), m_reg(reg) {

    }

    [[nodiscard]] uint64_t get_reg() const {
        return m_reg;
    }
private:
    uint64_t m_reg;
};