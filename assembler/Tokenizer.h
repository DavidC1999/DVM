#pragma once

#include <string>
#include <unordered_map>
#include <utility>

#include "shared.h"

#include "tokens/Tokens.h"
#include "Macro.h"

class Tokenizer {

public:
    explicit Tokenizer(std::string text) : m_text(std::move(text)) {

    }

    token_list_t tokenize();

private:
    std::unordered_map<std::string, AbstractInstruction> instructions {
        std::make_pair("halt", ABSTR_INSTR_HALT),
        std::make_pair("mov", ABSTR_INSTR_MOV),
        std::make_pair("ld", ABSTR_INSTR_LD),
        std::make_pair("st", ABSTR_INSTR_ST),
        std::make_pair("add", ABSTR_INSTR_ADD),
        std::make_pair("sub", ABSTR_INSTR_SUB),
        std::make_pair("mul", ABSTR_INSTR_MUL),
        std::make_pair("div", ABSTR_INSTR_DIV),
        std::make_pair("or", ABSTR_INSTR_OR),
        std::make_pair("nor", ABSTR_INSTR_NOR),
        std::make_pair("and", ABSTR_INSTR_AND),
        std::make_pair("nand", ABSTR_INSTR_NAND),
        std::make_pair("xor", ABSTR_INSTR_XOR),
        std::make_pair("xnor", ABSTR_INSTR_XNOR),
        std::make_pair("not", ABSTR_INSTR_NOT),
        std::make_pair("cmp", ABSTR_INSTR_CMP),
        std::make_pair("jmp", ABSTR_INSTR_JMP),
        std::make_pair("jg", ABSTR_INSTR_JMP_G),
        std::make_pair("jge", ABSTR_INSTR_JMP_GE),
        std::make_pair("jl", ABSTR_INSTR_JMP_L),
        std::make_pair("jle", ABSTR_INSTR_JMP_LE),
        std::make_pair("je", ABSTR_INSTR_JMP_E),
        std::make_pair("jne", ABSTR_INSTR_JMP_NE),
        std::make_pair("out", ABSTR_INSTR_OUT),
        std::make_pair("push", ABSTR_INSTR_PUSH),
        std::make_pair("pop", ABSTR_INSTR_POP),
    };

    static std::string get_word(std::string::iterator& it);
    static std::string get_digits(std::string::iterator& it);

    bool is_end_macro(std::string::iterator& it);
    void define_macro(std::string::iterator& it);
    void expand_macro(token_list_t::iterator &macro_start, const Macro &macro);

    static bool is_digit(char c);
    static bool is_alphanum(char c);

    static std::string str_tolower(std::string s);

    void panic(const std::string &message) const;

    std::string m_text;

    token_list_t m_tokens;

    int m_curr_line = 1;

    std::unordered_map<std::string, Macro> m_macro_table {};
};