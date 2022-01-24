# Assembler

## Flags
Flags are updated by the `cmp` instruction discussed later. They are used by the various jump instructions.
The flags are the same as found in the [VM README](/VM/README.md). They are described here as well for convenience.

| **Flag** | **Description**       |
|----------|-----------------------|
| G        | Greater than          |
| GE       | Greater than or equal |
| L        | Less than             |
| LE       | Less than or equal    |
| E        | Equal                 |

## Instructions
The basis of the assembly language are the instructions it implements. These instructions will assemble to one of the options defined in the [VM README](/VM/README.md).

Instructions in the Assembler are sometimes referred to as "abstract instructions" because they can assemble to different concrete instructions.

Instructions with multiple operands may have their operands separated by space, comma, or both.

Currently the following abstract instructions are defined:
### halt
*description:* halts the machine

*operands:*
- none

*can assemble to:*
- INSTR_HALT
### mov
*description:* copies a value from the second operand to the register in the first operand

*operands:*
- REGISTER
- REGISTER | IMMEDIATE

*can assemble to:*
- INSTR_MOV_REG
- INSTR_MOV_IMM

### ld
*description:* loads a value pointed to by the second operand to the register in the first operand

*operands:*
- REGISTER
- REGISTER | IMMEDIATE

*can assemble to:*
- INSTR_LD_REG
- INSTR_LD_IMM

### st
*description:* stores the contents of the register of the first operand to the address pointed to by the second operand

*operands:*
- REGISTER
- REGISTER | IMMEDIATE

*can assemble to:*
- INSTR_LD_REG
- INSTR_LD_IMM

### arithmetic
*instructions:*
- add
- sub
- mul
- div
- or
- nor
- and
- nand
- xor
- xnor

*description:* various possible arithmetic operations on two operands. Stores the result back to the first operand.

*operands:*
- REGISTER
- REGISTER | IMMEDIATE

*can assemble to:*
- INSTR_ADD_IMM
- INSTR_ADD_REG
- INSTR_SUB_IMM
- INSTR_SUB_REG
- INSTR_MUL_IMM
- INSTR_MUL_REG
- INSTR_DIV_IMM
- INSTR_DIV_REG
- INSTR_OR_IMM
- INSTR_OR_REG
- INSTR_NOR_IMM
- INSTR_NOR_REG
- INSTR_AND_IMM
- INSTR_AND_REG
- INSTR_NAND_IMM
- INSTR_NAND_REG
- INSTR_XOR_IMM
- INSTR_XOR_REG
- INSTR_XNOR_IMM
- INSTR_XNOR_REG

### not
*description:* bitwise inversion of register

*operands:*
- REGISTER

*can assemble to:*
- INSTR_NOT_REG

### cmp
*description:* compares two values in the order they are given. Updates the system flags accordingly.

*operands:*
- REGISTER
- REGISTER | IMMEDIATE

*can assemble to:*
- INSTR_CMP_IMM
- INSTR_CMP_REG

### jmp
*description:* unconditional jump

*operands*
- IMMEDIATE

*can assemble to:*
- INSTR_JMP

### jg
*description:* conditional jump. Jumps if greater than flag is set, otherwise continues to next instruction

*operands*
- IMMEDIATE

*can assemble to:*
- INSTR_JMP_G

### jge
*description:* conditional jump. Jumps if greater than or equal flag is set, otherwise continues to next instruction

*operands*
- IMMEDIATE

*can assemble to:*
- INSTR_JMP_GE

### jl
*description:* conditional jump. Jumps if less than flag is set, otherwise continues to next instruction

*operands*
- IMMEDIATE

*can assemble to:*
- INSTR_JMP_L

### jle
*description:* conditional jump. Jumps if less than or equal flag is set, otherwise continues to next instruction

*operands*
- IMMEDIATE

*can assemble to:*
- INSTR_JMP_LE

### je
*description:* conditional jump. Jumps if equal flag is set, otherwise continues to next instruction

*operands*
- IMMEDIATE

*can assemble to:*
- INSTR_JMP_E

### jne
*description:* conditional jump. Jumps if equal flag is not set, otherwise continues to next instruction

*operands*
- IMMEDIATE

*can assemble to:*
- INSTR_JMP_NE

### out
*description:* outputs operand to stdout.
This is a rudimentary way of interacting with the OS. A more robust way should be implemented in the future.

*operands*
- REGISTER | IMMEDIATE

*can assemble to:*
- INSTR_OUT_REG
- INSTR_OUT_IMM

### push
*description:* pushes value of operand to the stack

*operands*
- REGISTER | IMMEDIATE

*can assemble to:*
- INSTR_PUSH_IMM
- INSTR_PUSH_REG

### pop
*description:* pops value off the top of the stack, and copies it to a register. Crashes the VM if popping off an empty stack.

*operands*
- REGISTER

*can assemble to:*
- INSTR_POP


## Labels
For convenience of the programmer, you can define labels in your program. These labels are words, and can be used wherever an immediate value is expected.

Example:
```asm
mov r0, 0
loop:
    out r0
    add r0, 1
    cmp r0, 10
    jge break_loop
    jmp loop
break_loop:
    halt
```

will output
```
0
1
2
3
4
5
6
7
8
9
```

## Comments
Single-line comments:
```asm
mov r0, 10
; this is a comment
; add r0, 10
out r0
```

Multi-line comments:
```asm
/*
    This is a multi-line comment
    AUTHOR: me
*/
```