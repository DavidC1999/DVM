#pragma once

#include <cstdint>
#include <string>

#include "Token.h"


class CommaToken : public Token {
public:
    static const uint16_t TYPE_ID = __COUNTER__;
    SET_DEBUG_NAME(COMMA)

    explicit CommaToken(uint64_t line) :
            Token(TYPE_ID, line) {
    }
};