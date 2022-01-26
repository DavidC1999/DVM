#pragma once

#include <list>
#include <string>
#include <unordered_map>
#include <cstdint>

typedef std::list<std::pair<uint64_t, std::string>> expression_tokens_t;

class ExpressionEvaluator {

public:

    enum TokenType {
        PLUS,
        MINUS,
        DIV,
        MULT,
        POW,
        NUMBER,
        LPAREN,
        RPAREN,
        WORD
    };

    expression_tokens_t tokenize(std::string &text);

    uint64_t evaluate(const expression_tokens_t &tokens);

    void define_symbol(const std::string &name, uint64_t value);

private:

    static std::string get_word(std::string::iterator &it);

    static std::string get_digits(std::string::iterator &it);

    std::unordered_map<std::string, uint64_t> m_symbol_table;
};

