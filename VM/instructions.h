#pragma once

#include <stack>

#include "../general.h"
#include "shared.h"
#include "Memory.h"

enum Flag_bits {
    FLG_G = 0,
    FLG_GE,
    FLG_L,
    FLG_LE,
    FLG_E,
};

void instr_st_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_st_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_ld_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_ld_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_mov_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_mov_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_add_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_add_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_sub_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_sub_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_mul_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_mul_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_div_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_div_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_or_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_or_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_nor_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_nor_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_and_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_and_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_nand_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_nand_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_xor_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_xor_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_xnor_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_xnor_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_not_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_cmp_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs, uint8_t &flags);

void instr_cmp_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs, uint8_t &flags);

void instr_jmp(Memory &mem, uint64_t &pc);

void instr_jmp_g(Memory &mem, uint64_t &pc, uint8_t &flags);

void instr_jmp_ge(Memory &mem, uint64_t &pc, uint8_t &flags);

void instr_jmp_l(Memory &mem, uint64_t &pc, uint8_t &flags);

void instr_jmp_le(Memory &mem, uint64_t &pc, uint8_t &flags);

void instr_jmp_e(Memory &mem, uint64_t &pc, uint8_t &flags);

void instr_jmp_ne(Memory &mem, uint64_t &pc, uint8_t &flags);

void instr_out_imm(Memory &mem, uint64_t &pc);

void instr_out_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs);

void instr_push_imm(Memory &mem, uint64_t &pc, std::stack<uint64_t> &stack);

void instr_push_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs, std::stack<uint64_t> &stack);

void instr_pop(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs, std::stack<uint64_t> &stack);