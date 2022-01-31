#pragma once

#include <string>

#include "Token.h"
#include "../../general.h"


class WordToken : public Token {
public:
    static const uint16_t TYPE_ID = __COUNTER__;
    SET_DEBUG_NAME(WORD)

    WordToken(std::string& word, uint64_t line) :
        Token(TYPE_ID, line), m_word(word)
    {}

    std::unique_ptr<Token> clone() override {
        return std::make_unique<WordToken>(m_word, m_line);
    }


    [[nodiscard]] std::string get_word() const {
        return m_word;
    }
private:
    std::string m_word;
};