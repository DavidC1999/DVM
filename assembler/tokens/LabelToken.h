#pragma once

#include <cstdint>
#include <string>

#include "Token.h"


class LabelToken : public Token {
public:
    static const uint16_t TYPE_ID = __COUNTER__;
    SET_DEBUG_NAME(LABEL)

    LabelToken(std::string name, uint64_t line) :
            Token(TYPE_ID, line), m_name(std::move(name)) {}

    std::unique_ptr<Token> clone() override {
        return std::make_unique<LabelToken>(m_name, m_line);
    }

    [[nodiscard]] const std::string &get_name() const {
        return m_name;
    }

private:
    std::string m_name;
};