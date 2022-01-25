#pragma once

#include <string>
#include <iostream>
#include <list>
#include <memory>
#include <utility>
#include <cstdint>

#define SET_DEBUG_NAME(name) constexpr static const char* DEBUG_NAME = "<" #name ">";

class Token {

protected:
    Token(uint16_t type_id, uint64_t line) :
            m_type_id(type_id), m_line(line) {}

public:

    Token(const Token &other) :
            m_type_id(other.get_type_id()), m_line(other.get_line()) {}

    virtual std::unique_ptr<Token> clone() = 0;

    [[nodiscard]] uint64_t get_line() const {
        return m_line;
    }

    [[nodiscard]] uint16_t get_type_id() const {
        return m_type_id;
    }

    virtual ~Token() = default;

protected:

    uint16_t m_type_id;
    uint64_t m_line;

};

typedef std::list<std::unique_ptr<Token>> token_list_t;

std::ostream &operator<<(std::ostream &os, const Token &token);