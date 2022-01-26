#include "ExpressionEvaluator.h"

#include <sstream>

#include "shared.h"

std::string ExpressionEvaluator::get_word(std::string::iterator &it) {
    std::stringstream acc;

    while (is_alphanum(*it)) {
        acc << *it;
        ++it;
    }

    return acc.str();
}

std::string ExpressionEvaluator::get_digits(std::string::iterator &it) {
    std::stringstream acc;

    while (is_digit(*it)) {
        acc << *it;
        ++it;
    }

    return acc.str();
}

expression_tokens_t ExpressionEvaluator::tokenize(std::string &text) {
    expression_tokens_t out;

    auto it = text.begin();

    while (it != text.end()) {
        if(*it == ' ') {
            ++it;
            continue;
        }
        if (*it == '+') {
            out.emplace_back(std::make_pair(PLUS, ""));
            ++it;
            continue;
        }
        if (*it == '-') {
            out.emplace_back(std::make_pair(MINUS, ""));
            ++it;
            continue;
        }
        if (*it == '/') {
            out.emplace_back(std::make_pair(DIV, ""));
            ++it;
            continue;
        }
        if (*it == '*') {
            out.emplace_back(std::make_pair(MULT, ""));
            ++it;
            continue;
        }
        if (*it == '^') {
            out.emplace_back(std::make_pair(POW, ""));
            ++it;
            continue;
        }
        if (*it == '(') {
            out.emplace_back(std::make_pair(LPAREN, ""));
            ++it;
            continue;
        }
        if (*it == ')') {
            out.emplace_back(std::make_pair(RPAREN, ""));
            ++it;
            continue;
        }
        if (is_digit(*it)) {
            std::string digits = get_digits(it);
            out.emplace_back(std::make_pair(NUMBER, digits));
            continue;
        }
        if (is_alphanum(*it)) {
            std::string word = get_word(it);
            out.emplace_back(std::make_pair(WORD, word));
            continue;
        }
    }

    return out;
}

uint64_t ExpressionEvaluator::evaluate(const expression_tokens_t &tokens) {
    (void) tokens;
    return 0;
}

void ExpressionEvaluator::define_symbol(const std::string &name, uint64_t value) {
    m_symbol_table.insert(std::make_pair(name, value));
}
