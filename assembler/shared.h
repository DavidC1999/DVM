#pragma once

#include <unordered_map>

// General instruction types
// e.g. MOV has two variants in bytecode, but in assembly it's the same word
enum AbstractInstruction {
    ABSTR_INSTR_HALT = 0,
    ABSTR_INSTR_MOV,
    ABSTR_INSTR_LD,
    ABSTR_INSTR_ST,
    ABSTR_INSTR_ADD,
    ABSTR_INSTR_SUB,
    ABSTR_INSTR_MUL,
    ABSTR_INSTR_DIV,
    ABSTR_INSTR_OR,
    ABSTR_INSTR_NOR,
    ABSTR_INSTR_AND,
    ABSTR_INSTR_NAND,
    ABSTR_INSTR_XOR,
    ABSTR_INSTR_XNOR,
    ABSTR_INSTR_NOT,
    ABSTR_INSTR_CMP,
    ABSTR_INSTR_JMP,    // unconditional jump
    ABSTR_INSTR_JMP_G,  // jump if greater
    ABSTR_INSTR_JMP_GE, // jump if greater or equal
    ABSTR_INSTR_JMP_L,  // jump if less 
    ABSTR_INSTR_JMP_LE, // jump if less or equal
    ABSTR_INSTR_JMP_E,  // jump if equal
    ABSTR_INSTR_JMP_NE, // jump if not equal
    ABSTR_INSTR_OUT,
    ABSTR_INSTR_PUSH,
    ABSTR_INSTR_POP,
};