# VM
The VM is a "von Neumann" (in airquotes for a reason) machine. With
- 64-bit address space
- 15 general-purpose registers
- 64-bit stack

Each instruction is one byte, and is followed by its operands. The operands can be of varying length depending
on its associated instruction. Current instructions:

### INSTR_HALT

*description:* Halts the machine

*operands*
- none

### INSTR_MOV_IMM
*description:* Moves an immediate value into a general-purpose register

*operands*
- register (1 byte)
- immediate value (8 bytes)

### INSTR_MOV_REG
*description:* Copies the contents of one register to another

*operands*
- register to copy to (1 byte)
- register to copy from (1 byte)

### INSTR_LD_IMM
*description:* Loads contents from an immediate address to a register 

*operands*
- register (1 byte)
- address to load from (8 bytes)

### INSTR_LD_REG
*description:* Loads contents from an address pointed to by a register, to a register

*operands*
- register to load to (1 byte)
- register containing the address to load from (1 byte)

### INSTR_ST_IMM
*description:* Stores a register value into an immediate address in memory

*operands*
- register (1 byte)
- address to store to (8 bytes)

### INSTR_ST_REG
*description:* Stores a register value into an address pointed to by a register

*operands*
- register with value to store (1 byte)
- register pointing to address to store to (1 byte)

### Arithmetic instructions
There's a bunch of arithmetic instructions. I will not list them all out. This is the basic gist of it:

*description:* Performs an arithmetic instruction on two register values. Value is stored back to first register.

*operands:*
- register (1 byte)
- register (1 byte)

*Associated instructions:*
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

### INSTR_NOT_REG
*description:* inverts the value in a register

*operands*
- register to invert (1 byte)

### INSTR_CMP_IMM
*description:* compares the value from a certain register with an immediate value. Modifies the flags appropriately

*operands*
- register to compare (1 byte)
- immediate value to compare (8 bytes)

comparison is in order of operands. E.g.
```asm
; if r0 > 10, greater than flag will be high
cmp r0, 10
```

### INSTR_CMP_REG
*description:* compares the values from two registers. Modifies the flags appropriately

*operands*
- register to compare (1 byte)
- register to compare (1 byte)

Comparison order is the same as its immediate counterpart

### INSTR_JMP
*description:* unconditional jump

*operands*
- address to jump to (8 bytes)

### INSTR_JMP_G
*description:* conditional jump. Jumps if greater than flag is set, otherwise continues to next instruction

*operands*
- address to jump to (8 bytes)

### INSTR_JMP_GE
*description:* conditional jump. Jumps if greater than or equal flag is set, otherwise continues to next instruction

*operands*
- address to jump to (8 bytes)

### INSTR_JMP_L
*description:* conditional jump. Jumps if less than flag is set, otherwise continues to next instruction

*operands*
- address to jump to (8 bytes)

### INSTR_JMP_LE
*description:* conditional jump. Jumps if less than or equal flag is set, otherwise continues to next instruction

*operands*
- address to jump to (8 bytes)

### INSTR_JMP_E
*description:* conditional jump. Jumps if equal flag is set, otherwise continues to next instruction

*operands*
- address to jump to (8 bytes)

### INSTR_JMP_NE
*description:* conditional jump. Jumps if equal flag is not set, otherwise continues to next instruction

*operands*
- address to jump to (8 bytes)

### INSTR_OUT_IMM
*description:* outputs an immediate value to stdout
This is a rudimentary way of interacting with the OS. A more robust way should be implemented in the future.

*operands*
- immediate value (8 bytes)

### INSTR_OUT_REG
*description:* outputs a value from a register to stdout
This is a rudimentary way of interacting with the OS. A more robust way should be implemented in the future.

*operands*
- register (1 byte)

### INSTR_PUSH_IMM
*description:* push an immediate value to the stack

*operands*
- immediate value (8 bytes)

### INSTR_PUSH_REG
*description:* push a value from a register to the stack

*operands*
- register (1 byte)

### INSTR_POP
*description:* pops a value off the stack, and copies it to a register
crashes the VM if popping from an empty stack

*operands*
- register (1 byte)
