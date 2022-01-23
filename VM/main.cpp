#include <iostream>
#include <cstdint>
#include <array>
#include <fstream>
#include <iterator>
#include <stack>

#include "../general.h"
#include "shared.h"
#include "Memory.h"
#include "instructions.h"

#define FILE_PATH "D:\\Users\\David\\Documents\\programming\\VM\\program.bin"


//std::map<uint64_t, uint64_t> mem;

program_t read_program(const char *file_path) {
    std::ifstream file(file_path, std::ios_base::binary);
    if (file.is_open()) {
        file.unsetf(std::ios::skipws);

        std::streampos file_size;

        file.seekg(0, std::ios::end);
        file_size = file.tellg();
        file.seekg(0, std::ios::beg);

        program_t contents;
        contents.reserve(file_size);
        contents.insert(contents.begin(),
                        std::istream_iterator<uint8_t>(file),
                        std::istream_iterator<uint8_t>());

        return contents;
    } else {
        std::cout << "Could not open file: " << file_path << std::endl;
        std::exit(1);
    }
}

void print_reg_state(const std::array<uint64_t, REG_AMT> &regs) {
    std::cout << "------------------" << std::endl;
    std::cout << "Register state:" << std::endl;
    for (int i = 0; i < REG_AMT; ++i) {
        std::cout << "\t r" << i << ": " << regs[i] << std::endl;
    }
    std::cout << "------------------" << std::endl;
}

int main() {
    Memory mem;
    uint8_t flags = 0;
    std::array<uint64_t, REG_AMT> regs = {0};
    std::stack<uint64_t> stack;

    program_t program = read_program(FILE_PATH);

    mem.load_program(program);
    mem.print_contents();

    uint64_t pc = 0;

    auto instruction = (Instruction) mem.get_value(pc++);
    while (instruction) { // HALT is defined as 0, so will automatically stop the loop
        switch (instruction) {
            case INSTR_HALT: {
                // Will never be reached, will just avoid a compile error due to exhaustive switch statement
            }
            case INSTR_ST_IMM: {
                instr_st_imm(mem, pc, regs);
                break;
            }
            case INSTR_ST_REG: {
                instr_st_reg(mem, pc, regs);
                break;
            }
            case INSTR_LD_IMM: {
                instr_ld_imm(mem, pc, regs);
                break;
            }
            case INSTR_LD_REG: {
                instr_ld_reg(mem, pc, regs);
                break;
            }
            case INSTR_MOV_IMM: {
                instr_mov_imm(mem, pc, regs);
                break;
            }
            case INSTR_MOV_REG: {
                instr_mov_reg(mem, pc, regs);
                break;
            }
            case INSTR_ADD_REG: {
                instr_add_reg(mem, pc, regs);
                break;
            }
            case INSTR_ADD_IMM: {
                instr_add_imm(mem, pc, regs);
                break;
            }
            case INSTR_SUB_REG: {
                instr_sub_reg(mem, pc, regs);
                break;
            }
            case INSTR_SUB_IMM: {
                instr_sub_imm(mem, pc, regs);
                break;
            }
            case INSTR_MUL_REG: {
                instr_mul_reg(mem, pc, regs);
                break;
            }
            case INSTR_MUL_IMM: {
                instr_mul_imm(mem, pc, regs);
                break;
            }
            case INSTR_DIV_REG: {
                instr_div_reg(mem, pc, regs);
                break;
            }
            case INSTR_DIV_IMM: {
                instr_div_imm(mem, pc, regs);
                break;
            }
            case INSTR_OR_REG: {
                instr_or_reg(mem, pc, regs);
                break;
            }
            case INSTR_OR_IMM: {
                instr_or_imm(mem, pc, regs);
                break;
            }
            case INSTR_NOR_REG: {
                instr_nor_reg(mem, pc, regs);
                break;
            }
            case INSTR_NOR_IMM: {
                instr_nor_imm(mem, pc, regs);
                break;
            }
            case INSTR_AND_REG: {
                instr_and_reg(mem, pc, regs);
                break;
            }
            case INSTR_AND_IMM: {
                instr_and_imm(mem, pc, regs);
                break;
            }
            case INSTR_NAND_REG: {
                instr_nand_reg(mem, pc, regs);
                break;
            }
            case INSTR_XOR_REG: {
                instr_xor_reg(mem, pc, regs);
                break;
            }
            case INSTR_XOR_IMM: {
                instr_xor_imm(mem, pc, regs);
                break;
            }
            case INSTR_XNOR_REG: {
                instr_xnor_reg(mem, pc, regs);
                break;
            }
            case INSTR_XNOR_IMM: {
                instr_xnor_imm(mem, pc, regs);
                break;
            }
            case INSTR_NAND_IMM: {
                instr_nand_imm(mem, pc, regs);
                break;
            }
            case INSTR_NOT_REG: {
                instr_not_reg(mem, pc, regs);
                break;
            }
            case INSTR_CMP_IMM: {
                instr_cmp_imm(mem, pc, regs, flags);
                break;
            }
            case INSTR_CMP_REG: {
                instr_cmp_reg(mem, pc, regs, flags);
                break;
            }
            case INSTR_JMP: {
                instr_jmp(mem, pc);
                break;
            }
            case INSTR_JMP_G: {
                instr_jmp_g(mem, pc, flags);
                break;
            }
            case INSTR_JMP_GE: {
                instr_jmp_ge(mem, pc, flags);
                break;
            }
            case INSTR_JMP_L: {
                instr_jmp_l(mem, pc, flags);
                break;
            }
            case INSTR_JMP_LE: {
                instr_jmp_le(mem, pc, flags);
                break;
            }
            case INSTR_JMP_E: {
                instr_jmp_e(mem, pc, flags);
                break;
            }
            case INSTR_JMP_NE: {
                instr_jmp_ne(mem, pc, flags);
                break;
            }
            case INSTR_OUT_IMM: {
                instr_out_imm(mem, pc);
                break;
            }
            case INSTR_OUT_REG: {
                instr_out_reg(mem, pc, regs);
                break;
            }
            case INSTR_PUSH_IMM: {
                instr_push_imm(mem, pc, stack);
                break;
            }
            case INSTR_PUSH_REG: {
                instr_push_reg(mem, pc, regs, stack);
                break;
            }
            case INSTR_POP: {
                instr_pop(mem, pc, regs, stack);
                break;
            }
        }
        instruction = (Instruction) mem.get_value(pc++);
    }
    std::cout << "Execution stopped" << std::endl;
    print_reg_state(regs);
//    print_mem_state();
}