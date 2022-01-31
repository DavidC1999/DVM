#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "tokens/Tokens.h"

class Macro {
public:
    Macro(std::string name/*, std::vector<std::string> args*/, token_list_t body, uint64_t line) :
            m_name(std::move(name))/*, m_args(std::move(args))*/, m_body(std::move(body)), m_line(line) {

    }

    Macro(Macro &&other)  noexcept {
        m_name = std::move(other.m_name);
        m_body = std::move(other.m_body);
        m_line = other.m_line;
    }

    [[nodiscard]] const std::string &get_name() const {
        return m_name;
    }

    /*
    [[nodiscard]] const std::vector<std::string> &get_args() const {
        return m_args;
    }
     */

    [[nodiscard]] token_list_t &get_body() {
        return m_body;
    }

    [[nodiscard]] const token_list_t &get_body() const {
        return m_body;
    }

    [[nodiscard]] token_list_t copy_body() const {
        token_list_t out;
        for(const auto &token : m_body) out.push_back(token->clone());
        return out;
    }

    [[nodiscard]] uint64_t get_line() const {
        return m_line;
    }

private:
    std::string m_name;

//    std::vector<std::string> m_args;
    token_list_t m_body;
    uint64_t m_line;
};