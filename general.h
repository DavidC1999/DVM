#pragma once

// general types used by multiple executables

#include <cstdint>
#include <vector>
#include <array>
#include <string>

enum Instruction {
    INSTR_HALT = 0,
    INSTR_MOV_IMM,
    INSTR_MOV_REG,
    INSTR_LD_IMM,
    INSTR_LD_REG,
    INSTR_ST_IMM,
    INSTR_ST_REG,
    INSTR_ADD_IMM,
    INSTR_ADD_REG,
    INSTR_SUB_IMM,
    INSTR_SUB_REG,
    INSTR_MUL_IMM,
    INSTR_MUL_REG,
    INSTR_DIV_IMM,
    INSTR_DIV_REG,
    INSTR_OR_IMM,
    INSTR_OR_REG,
    INSTR_NOR_IMM,
    INSTR_NOR_REG,
    INSTR_AND_IMM,
    INSTR_AND_REG,
    INSTR_NAND_IMM,
    INSTR_NAND_REG,
    INSTR_XOR_IMM,
    INSTR_XOR_REG,
    INSTR_XNOR_IMM,
    INSTR_XNOR_REG,
    INSTR_NOT_REG,
    INSTR_CMP_IMM,
    INSTR_CMP_REG,
    INSTR_JMP,    // unconditional jump
    INSTR_JMP_G,  // jump if greater
    INSTR_JMP_GE, // jump if greater or equal
    INSTR_JMP_L,  // jump if less 
    INSTR_JMP_LE, // jump if less or equal
    INSTR_JMP_E,  // jump if equal
    INSTR_JMP_NE, // jump if not equal
    INSTR_OUT_IMM,
    INSTR_OUT_REG,
    INSTR_PUSH_IMM,
    INSTR_PUSH_REG,
    INSTR_POP
};

const char* instruction_as_string(Instruction instr);

typedef std::vector<uint8_t> program_t;