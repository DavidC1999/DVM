#pragma once

#include <cstdint>
// #include <vector>
#include <cstdint>
#include <array>
#include <list>
#include <unordered_map>

#include "tokens/Token.h"

#include "../general.h"
#include "AssemblerBytes.h"
#include "shared.h"

#include "tokens/WordToken.h"
#include "tokens/NumberToken.h"
#include "tokens/RegisterToken.h"
#include "tokens/InstructionToken.h"
#include "tokens/LabelToken.h"
#include "tokens/CommaToken.h"
#include "Macro.h"


class Assembler {

public:
    explicit Assembler(token_list_t tokens)
            : m_tokens(std::move(tokens)) {}

    program_t assemble();

private:

    void expect_more_tokens(token_list_t::iterator const &it, uint8_t amt);

    static std::vector<uint8_t> num_to_bytes(uint64_t num);

    template<class T> void expect_token_type(const Token &token);

    void parse_instruction(token_list_t::iterator &it);

    void parse_binary_reg_instruction(Instruction instr_imm, Instruction instr_reg, token_list_t::iterator &it);

    void parse_unary_reg_instruction(Instruction instr_imm, Instruction instr_reg, token_list_t::iterator &it);

    void parse_jmp_instruction(Instruction jmp_instr, token_list_t::iterator &it);

    static void panic(std::string const &message, Token const &token);

    static void panic(std::string const &message, uint64_t line_num);

    token_list_t m_tokens;

    std::list<AssemblerBytes> m_program;

    std::unordered_map<std::string, uint64_t> m_symbol_table {};
};