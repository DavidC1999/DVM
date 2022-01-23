#include <iostream>
#include "instructions.h"

void instr_st_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg = mem.get_value(pc++);
    uint64_t addr = mem.get_value_64(pc);
    pc += 8;

    uint64_t value = regs[reg];
    mem.set_value_64(addr, value);
}

void instr_st_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg0 = mem.get_value(pc++);
    uint8_t reg1 = mem.get_value(pc++);
    uint64_t value = regs[reg0];
    uint64_t addr = regs[reg1];

    mem.set_value_64(addr, value);
}

void instr_ld_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg = mem.get_value(pc++);
    uint64_t addr = mem.get_value_64(pc);
    pc += 8;

    regs[reg] = mem.get_value_64(addr);
}

void instr_ld_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg0 = mem.get_value(pc++);
    uint64_t reg1 = mem.get_value(pc++);
    uint64_t addr = regs[reg1];

    regs[reg0] = mem.get_value_64(addr);
}

void instr_mov_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg = mem.get_value(pc++);
    uint64_t value = mem.get_value_64(pc);
    pc += 8;

    regs[reg] = value;
}

void instr_mov_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg_to = mem.get_value(pc++);
    uint8_t reg_from = mem.get_value(pc++);

    regs[reg_to] = regs[reg_from];
}

void instr_add_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg0 = mem.get_value(pc++);
    uint8_t reg1 = mem.get_value(pc++);
    regs[reg0] = regs[reg0] + regs[reg1];
}

void instr_add_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg = mem.get_value(pc++);
    uint8_t value = mem.get_value_64(pc);
    pc += 8;
    regs[reg] = regs[reg] + value;
}

void instr_sub_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg = mem.get_value(pc++);
    uint8_t value = mem.get_value_64(pc);
    pc += 8;
    regs[reg] = regs[reg] - value;
}

void instr_sub_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg0 = mem.get_value(pc++);
    uint8_t reg1 = mem.get_value(pc++);
    regs[reg0] = regs[reg0] - regs[reg1];
}

void instr_mul_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg = mem.get_value(pc++);
    uint8_t value = mem.get_value_64(pc);
    pc += 8;
    regs[reg] = regs[reg] * value;
}

void instr_mul_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg0 = mem.get_value(pc++);
    uint8_t reg1 = mem.get_value(pc++);
    regs[reg0] = regs[reg0] * regs[reg1];
}

void instr_div_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg = mem.get_value(pc++);
    uint8_t value = mem.get_value_64(pc);
    pc += 8;
    regs[reg] = regs[reg] / value;
}

void instr_div_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg0 = mem.get_value(pc++);
    uint8_t reg1 = mem.get_value(pc++);
    regs[reg0] = regs[reg0] / regs[reg1];
}

void instr_or_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg = mem.get_value(pc++);
    uint8_t value = mem.get_value_64(pc);
    pc += 8;
    regs[reg] = regs[reg] | value;
}

void instr_or_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg0 = mem.get_value(pc++);
    uint8_t reg1 = mem.get_value(pc++);
    regs[reg0] = regs[reg0] | regs[reg1];
}

void instr_nor_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg = mem.get_value(pc++);
    uint8_t value = mem.get_value_64(pc);
    pc += 8;
    regs[reg] = ~(regs[reg] | value);
}

void instr_nor_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg0 = mem.get_value(pc++);
    uint8_t reg1 = mem.get_value(pc++);
    regs[reg0] = ~(regs[reg0] | regs[reg1]);
}

void instr_and_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg = mem.get_value(pc++);
    uint8_t value = mem.get_value_64(pc);
    pc += 8;
    regs[reg] = regs[reg] & value;
}

void instr_and_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg0 = mem.get_value(pc++);
    uint8_t reg1 = mem.get_value(pc++);
    regs[reg0] = regs[reg0] & regs[reg1];
}

void instr_nand_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg = mem.get_value(pc++);
    uint8_t value = mem.get_value_64(pc);
    pc += 8;
    regs[reg] = ~(regs[reg] & value);
}

void instr_nand_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg0 = mem.get_value(pc++);
    uint8_t reg1 = mem.get_value(pc++);
    regs[reg0] = ~(regs[reg0] & regs[reg1]);
}

void instr_xor_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg = mem.get_value(pc++);
    uint8_t value = mem.get_value_64(pc);
    pc += 8;
    regs[reg] = regs[reg] ^ value;
}

void instr_xor_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg0 = mem.get_value(pc++);
    uint8_t reg1 = mem.get_value(pc++);
    regs[reg0] = regs[reg0] ^ regs[reg1];
}

void instr_xnor_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg = mem.get_value(pc++);
    uint8_t value = mem.get_value_64(pc);
    pc += 8;
    regs[reg] = ~(regs[reg] ^ value);
}

void instr_xnor_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg0 = mem.get_value(pc++);
    uint8_t reg1 = mem.get_value(pc++);
    regs[reg0] = ~(regs[reg0] ^ regs[reg1]);
}

void instr_not_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg = mem.get_value(pc++);
    regs[reg] = ~(regs[reg]);
}

void instr_cmp_imm(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs, uint8_t &flags) {
    uint8_t reg = mem.get_value(pc++);
    uint64_t value0 = regs[reg];
    uint64_t value1 = mem.get_value_64(pc);
    pc += 8;

    flags = 0;
    if (value0 > value1)
        flags = flags | (1 << FLG_G);
    if (value0 >= value1)
        flags = flags | (1 << FLG_GE);
    if (value0 < value1)
        flags = flags | (1 << FLG_L);
    if (value0 <= value1)
        flags = flags | (1 << FLG_LE);
    if (value0 == value1)
        flags = flags | (1 << FLG_E);

}

void instr_cmp_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs, uint8_t &flags) {
    uint8_t reg0 = mem.get_value(pc++);
    uint8_t reg1 = mem.get_value(pc++);
    uint64_t value0 = regs[reg0];
    uint64_t value1 = regs[reg1];

    flags = 0;
    if (value0 > value1)
        flags = flags | (1 << FLG_G);
    if (value0 >= value1)
        flags = flags | (1 << FLG_GE);
    if (value0 < value1)
        flags = flags | (1 << FLG_L);
    if (value0 <= value1)
        flags = flags | (1 << FLG_LE);
    if (value0 == value1)
        flags = flags | (1 << FLG_E);
}

void instr_jmp(Memory &mem, uint64_t &pc) {
    uint64_t addr = mem.get_value_64(pc);
    // incrementing the program counter does nothing,
    // because we jump anyway
    // pc += 8;

    pc = addr;
}

void instr_jmp_g(Memory &mem, uint64_t &pc, uint8_t &flags) {
    uint64_t addr = mem.get_value_64(pc);
    if (flags & (1 << FLG_G)) {
        pc = addr;
    } else {
        pc += 8;
    }
}

void instr_jmp_ge(Memory &mem, uint64_t &pc, uint8_t &flags) {
    uint64_t addr = mem.get_value_64(pc);
    if (flags & (1 << FLG_GE)) {
        pc = addr;
    } else {
        pc += 8;
    }
}

void instr_jmp_l(Memory &mem, uint64_t &pc, uint8_t &flags) {
    uint64_t addr = mem.get_value_64(pc);
    if (flags & (1 << FLG_L)) {
        pc = addr;
    } else {
        pc += 8;
    }
}

void instr_jmp_le(Memory &mem, uint64_t &pc, uint8_t &flags) {
    uint64_t addr = mem.get_value_64(pc);
    if (flags & (1 << FLG_LE)) {
        pc = addr;
    } else {
        pc += 8;
    }
}

void instr_jmp_e(Memory &mem, uint64_t &pc, uint8_t &flags) {
    uint64_t addr = mem.get_value_64(pc);
    if (flags & (1 << FLG_E)) {
        pc = addr;
    } else {
        pc += 8;
    }
}

void instr_jmp_ne(Memory &mem, uint64_t &pc, uint8_t &flags) {
    uint64_t addr = mem.get_value_64(pc);
    if (!(flags & (1 << FLG_E))) {
        pc = addr;
    } else {
        pc += 8;
    }
}

void instr_out_imm(Memory &mem, uint64_t &pc) {
    uint64_t value = mem.get_value_64(pc);
    pc += 8;
    std::cout << "Program output: " << value << std::endl;
}

void instr_out_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs) {
    uint8_t reg = mem.get_value(pc++);
    std::cout << "Program output: " << regs[reg] << std::endl;
}

void instr_push_imm(Memory &mem, uint64_t &pc, std::stack<uint64_t> &stack) {
    uint64_t value = mem.get_value_64(pc);
    pc += 8;
    stack.push(value);
}

void instr_push_reg(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs, std::stack<uint64_t> &stack) {
    uint8_t reg = mem.get_value(pc++);
    uint64_t value = regs[reg];
    stack.push(value);
}

void instr_pop(Memory &mem, uint64_t &pc, std::array<uint64_t, REG_AMT> &regs, std::stack<uint64_t> &stack) {
    if(stack.empty()) {
        throw std::out_of_range("Tring to pop from empty stack");
    }

    uint8_t reg = mem.get_value(pc++);
    regs[reg] = stack.top();
    stack.pop();
}








