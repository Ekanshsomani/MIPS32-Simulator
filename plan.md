# MIPS Processor Details

## Instruction Set

Notes:
- R2 (wherever mentioned) implies that they were MIPS32 RELEASE 2 INSTRUCTION.

### Arithmetic Operations

```Markdown
| **Instruction**       | **Binary Form**                                                           |
|-----------------------|---------------------------------------------------------------------------|
| `ADD RD, RS, RT`      | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 100000               |
| `ADDI RD, RS, CONST16`| 001000 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX              |
| `ADDIU RD,RS, CONST16`| 001001 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX              |
| `ADDU RD, RS, RT`     | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 100001               |
| `CLO RD, RS`          | 011100 | rs: XXXXX | rt: 00000 | rd: XXXXX | 00000 | 100001               |
| `CLZ RD, RS`          | 011100 | rs: XXXXX | rt: 00000 | rd: XXXXX | 00000 | 100000               |
| `LA RD, LABEL`        | Pseudo-instruction, typically translates to `LUI` and `ORI` instructions  |
| `LI RD, IMM32`        | Pseudo-instruction, typically translates to `LUI` and `ORI` instructions  |
| `LUI RD, CONST16`     | 001111 | rs: 00000 | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX              |
| `MOVE RD, RS`         | Pseudo-instruction, translates to `ADDU RD, RS, $zero`                    |
| `NEGU RD, RS`         | Pseudo-instruction, translates to `SUBU RD, $zero, RS`                    |
| `SEB RD, RS` (R2)     | 000000 | rs: XXXXX | rt: 00000 | rd: XXXXX | 00000 | 011010               |
| `SEH RD, RS` (R2)     | 000000 | rs: XXXXX | rt: 00000 | rd: XXXXX | 00000 | 011011               |
| `SUB RD, RS, RT`      | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 100010               |
| `SUBU RD, RS, RT`     | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 100011               |
```

### Shift and Rotate Operations

```Markdown
| **Instruction**           | **Binary Form**                                                      |
|---------------------------|----------------------------------------------------------------------|
| `ROTR RD, RS, BITS5` (R2) | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | shamt: XXXXX | 000010   |
| `ROTRV RD, RS, RT`  (R2)  | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 000110          |
| `SLL RD, RS, SHIFT5`      | 000000 | 00000 | rt: XXXXX | rd: XXXXX | shamt: XXXXX | 000000       |
| `SLLV RD, RS, RT`         | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 000100          |
| `SRA RD, RS, SHIFT5`      | 000000 | 00000 | rt: XXXXX | rd: XXXXX | shamt: XXXXX | 000011       |
| `SRAV RD, RS, RT`         | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 000111          |
| `SRL RD, RS, SHIFT5`      | 000000 | 00000 | rt: XXXXX | rd: XXXXX | shamt: XXXXX | 000010       |
| `SRLV RD, RS, RT`         | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 000110          |
```

### Logical and BIT-Field Operations

```Markdown
| **Instruction**       | **Binary Form**                                                   |
|-----------------------|-------------------------------------------------------------------|
| `AND RD, RS, RT`      | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 100100       |
| `ANDI RD, RS, CONST16`| 001100 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX      |
| `EXTR2 RD, RS, P, S`  | Custom instruction, depends on specific implementation            |
| `INSR2 RD, RS, P, S`  | Custom instruction, depends on specific implementation            |
| `NOP`                 | 000000 | 00000 | 00000 | 00000 | 00000 | 000000                   |
| `NOR RD, RS, RT`      | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 100111       |
| `NOT RD, RS`          | Pseudo-instruction, translates to `NOR RD, RS, $zero`             |
| `OR RD, RS, RT`       | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 100101       |
| `ORI RD, RS, CONST16` | 001101 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX      |
| `WSBHR2 RD, RS`       | Custom instruction, depends on specific implementation            |
| `XOR RD, RS, RT`      | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 100110       |
| `XORI RD, RS, CONST16`| 001110 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX      |
```

### condition testing and conditional move operations

```Markdown
| **Instruction**       | **Binary Form**                                                 |
|-----------------------|-----------------------------------------------------------------|
| `MOVN RD, RS, RT`     | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 001011     |
| `MOVZ RD, RS, RT`     | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 001010     |
| `SLT RD, RS, RT`      | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 101010     |
| `SLTI RD, RS, CONST16`| 001010 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX    |
| `SLTIU RD,RS, CONST16`| 001011 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX    |
| `SLTU RD, RS, RT`     | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 101011     |
```

### Multiply and divide operations

```Markdown
| **Instruction**       | **Binary Form**                                               |
|-----------------------|---------------------------------------------------------------|
| `DIV RS, RT`          | 000000 | rs: XXXXX | rt: XXXXX | 00000 | 00000 | 011010       |
| `DIVU RS, RT`         | 000000 | rs: XXXXX | rt: XXXXX | 00000 | 00000 | 011011       |
| `MADD RS, RT`         | 011100 | rs: XXXXX | rt: XXXXX | 00000 | 00000 | 000000       |
| `MADDU RS, RT`        | 011100 | rs: XXXXX | rt: XXXXX | 00000 | 00000 | 000001       |
| `MSUB RS, RT`         | 011100 | rs: XXXXX | rt: XXXXX | 00000 | 00000 | 000100       |
| `MSUBU RS, RT`        | 011100 | rs: XXXXX | rt: XXXXX | 00000 | 00000 | 000101       |
| `MUL RD, RS, RT`      | 011100 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 000010   |
| `MULT RS, RT`         | 000000 | rs: XXXXX | rt: XXXXX | 00000 | 00000 | 011000       |
| `MULTU RS, RT`        | 000000 | rs: XXXXX | rt: XXXXX | 00000 | 00000 | 011001       |
```

### Accumulator Acess Operations

```Markdown
| **Instruction**       | **Binary Form**                                        |
|-----------------------|--------------------------------------------------------|
| `MFHI RD`             | 000000 | 00000 | 00000 | rd: XXXXX | 00000 | 010000    |
| `MFLO RD`             | 000000 | 00000 | 00000 | rd: XXXXX | 00000 | 010010    |
| `MTHI RS`             | 000000 | rs: XXXXX | 00000 | 00000 | 00000 | 010001    |
| `MTLO RS`             | 000000 | rs: XXXXX | 00000 | 00000 | 00000 | 010011    |
```

### Jumps and branches instructions

```Markdown
| **Instruction**       | **Binary Form**                                                   |
|-----------------------|-------------------------------------------------------------------|
| `B OFF18`             | 000100 | 00000 | 00000 | offset: XXXXXXXXXXXXXXXXXX               |
| `BAL OFF18`           | 000001 | 00000 | 10001 | offset: XXXXXXXXXXXXXXXXXX               |
| `BEQ RS, RT, OFF18`   | 000100 | rs: XXXXX | rt: XXXXX | offset: XXXXXXXXXXXXXXXXXX       |
| `BEQZ RS, OFF18`      | 000100 | rs: XXXXX | 00000 | offset: XXXXXXXXXXXXXXXXXX           |
| `BGEZ RS, OFF18`      | 000001 | rs: XXXXX | 00001 | offset: XXXXXXXXXXXXXXXXXX           |
| `BGEZAL RS, OFF18`    | 000001 | rs: XXXXX | 10001 | offset: XXXXXXXXXXXXXXXXXX           |
| `BGTZ RS, OFF18`      | 000111 | rs: XXXXX | 00000 | offset: XXXXXXXXXXXXXXXXXX           |
| `BLEZ RS, OFF18`      | 000110 | rs: XXXXX | 00000 | offset: XXXXXXXXXXXXXXXXXX           |
| `BLTZ RS, OFF18`      | 000001 | rs: XXXXX | 00000 | offset: XXXXXXXXXXXXXXXXXX           |
| `BLTZAL RS, OFF18`    | 000001 | rs: XXXXX | 10000 | offset: XXXXXXXXXXXXXXXXXX           |
| `BNE RS, RT, OFF18`   | 000101 | rs: XXXXX | rt: XXXXX | offset: XXXXXXXXXXXXXXXXXX       |
| `BNEZ RS, OFF18`      | 000101 | rs: XXXXX | 00000 | offset: XXXXXXXXXXXXXXXXXX           |
| `J ADDR28`            | 000010 | address: XXXXXXXXXXXXXXXXXXXXXXXXXXXX                    |
| `JAL ADDR28`          | 000011 | address: XXXXXXXXXXXXXXXXXXXXXXXXXXXX                    |
| `JALR RD, RS`         | 000000 | rs: XXXXX | 00000 | rd: XXXXX | 00000 | 001001           |
| `JR RS`               | 000000 | rs: XXXXX | 00000 | 00000 | 00000 | 001000               |
```

### load and store operations

```Markdown
| **Instruction**       | **Binary Form**                                                  |
|-----------------------|------------------------------------------------------------------|
| `LB RD, OFF16(RS)`    | 100000 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX     |
| `LBU RD, OFF16(RS)`   | 100100 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX     |
| `LH RD, OFF16(RS)`    | 100001 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX     |
| `LHU RD, OFF16(RS)`   | 100101 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX     |
| `LW RD, OFF16(RS)`    | 100011 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX     |
| `LWL RD, OFF16(RS)`   | 100010 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX     |
| `LWR RD, OFF16(RS)`   | 100110 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX     |
| `SB RS, OFF16(RT)`    | 101000 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX     |
| `SH RS, OFF16(RT)`    | 101001 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX     |
| `SW RS, OFF16(RT)`    | 101011 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX     |
| `SWL RS, OFF16(RT)`   | 101010 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX     |
| `SWR RS, OFF16(RT)`   | 101110 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX     |
| `ULW RD, OFF16(RS)`   | Custom instruction, depends on specific implementation           |
| `USW RS, OFF16(RT)`   | Custom instruction, depends on specific implementation           |
```

### atomic read-modify-write operations

```Markdown
| **Instruction**       | **Binary Form**                                                |
|-----------------------|----------------------------------------------------------------|
| `LL RD, OFF16(RS)`    | 110000 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX   |
| `SC RD, OFF16(RS)`    | 111000 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX   |
```

Ref: https://en.wikibooks.org/wiki/MIPS_Assembly/Instruction_Formats

## Registers

- 32 General purpose registers
  - `$zero`: Always holds the value 0.
  - `$at`: Reserved for the assembler.
  - `$v0`-`$v1`: Used for function return values.
  - `$a0`-`$a3`: Used for function arguments.
  - `$s0`-`$s7`: Saved registers.
  - `$t0`-`$t9`: Temporary registers.
  - `$k0`-`$k1`: Reserved for the OS Kernel.
  - `$gp`: Global pointer.
  - `$sp`: Stack pointer.
  - `$fp`: Frame pointer.
  - `$ra`: Return address.
- 32 Floating Points Registers - `$f0` to `$31` - Used for floating point operations
- Special Registers
  - Progam Counter (PC) - Holds the address of next instruction to be executed
  - HI and LO Registers: Used to store the results of certain arithmetic operations like multiplication and division.
  - Cycle Counter Register: Often referred to as the Count register (`$count`), it keeps track of the number of cycles.

## Memory Segments

- **Instruction Memory:** Memory map all the instructions to this segment. Address stored in program counter.
- **Data Segment:** Stores initialized global and static variables.
- **Block Started by Symbol (BSS) Segment:** Stores uninitialized global and static variables.
- **Heap:** Used for dynamic memory allocation.
- **Stack:** Used for function calls and local variables. Address stored at stack pointer (register 29)
- **Global Data Segment:** Stores global variables and constants. Address stored at global pointer (register 28)


# Plan

## Fetch (IF)

## Decode (ID)

## Execute (EX)

## Memory (MEM)

## Write Back (WB)


