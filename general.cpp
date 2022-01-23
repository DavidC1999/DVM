#include <unordered_map>
#include <string>

#include "general.h"

const char *instruction_as_string(Instruction instr) {
#define CASE(x) case x:\
    return #x;\
    break;

    switch (instr) {
        CASE(INSTR_HALT)
        CASE(INSTR_MOV_IMM)
        CASE(INSTR_MOV_REG)
        CASE(INSTR_LD_IMM)
        CASE(INSTR_LD_REG)
        CASE(INSTR_ST_IMM)
        CASE(INSTR_ST_REG)
        CASE(INSTR_ADD_IMM)
        CASE(INSTR_ADD_REG)
        CASE(INSTR_SUB_IMM)
        CASE(INSTR_SUB_REG)
        CASE(INSTR_MUL_IMM)
        CASE(INSTR_MUL_REG)
        CASE(INSTR_DIV_IMM)
        CASE(INSTR_DIV_REG)
        CASE(INSTR_OR_IMM)
        CASE(INSTR_OR_REG)
        CASE(INSTR_NOR_IMM)
        CASE(INSTR_NOR_REG)
        CASE(INSTR_AND_IMM)
        CASE(INSTR_AND_REG)
        CASE(INSTR_NAND_IMM)
        CASE(INSTR_NAND_REG)
        CASE(INSTR_XOR_IMM)
        CASE(INSTR_XOR_REG)
        CASE(INSTR_XNOR_IMM)
        CASE(INSTR_XNOR_REG)
        CASE(INSTR_NOT_REG)
        CASE(INSTR_CMP_IMM)
        CASE(INSTR_CMP_REG)
        CASE(INSTR_JMP)
        CASE(INSTR_JMP_G)
        CASE(INSTR_JMP_GE)
        CASE(INSTR_JMP_L)
        CASE(INSTR_JMP_LE)
        CASE(INSTR_JMP_E)
        CASE(INSTR_JMP_NE)
        CASE(INSTR_OUT_IMM)
        CASE(INSTR_OUT_REG)
        CASE(INSTR_PUSH_IMM)
        CASE(INSTR_PUSH_REG)
        CASE(INSTR_POP)
    }
#undef CASE
    return "unknown";
}