# MIPS Processor Details

## Instruction Set Release 2

Notes:
- R2 (wherever mentioned) implies that they were MIPS32 RELEASE 2 INSTRUCTION.

### Arithmetic Operations

```Markdown
| **Instruction**       | **Binary Form**                                                         |
|-----------------------|-------------------------------------------------------------------------|
| `ADD RD, RS, RT`      | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 100000             |
| `ADDI RD, RS, CONST16`| 001000 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX            |
| `ADDIU RD,RS, CONST16`| 001001 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX            |
| `ADDU RD, RS, RT`     | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 100001             |
| `CLO RD, RS`          | 011100 | rs: XXXXX | rt: 00000 | rd: XXXXX | 00000 | 100001             |
| `CLZ RD, RS`          | 011100 | rs: XXXXX | rt: 00000 | rd: XXXXX | 00000 | 100000             |
| `LA RD, LABEL`        | Pseudo-instruction, typically translates to `LUI` and `ORI` instructions|
| `LI RD, IMM32`        | Pseudo-instruction, typically translates to `LUI` and `ORI` instructions|
| `LUI RD, CONST16`     | 001111 | rs: 00000 | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX            |
| `MOVE RD, RS`         | Pseudo-instruction, translates to `ADDU RD, RS, $zero`                  |
| `NEGU RD, RS`         | Pseudo-instruction, translates to `SUBU RD, $zero, RS`                  |
| `SEB RD, RS` (R2)     | 000000 | rs: XXXXX | rt: 00000 | rd: XXXXX | 00000 | 011010             |
| `SEH RD, RS` (R2)     | 000000 | rs: XXXXX | rt: 00000 | rd: XXXXX | 00000 | 011011             |
| `SUB RD, RS, RT`      | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 100010             |
| `SUBU RD, RS, RT`     | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 100011             |
```

### Shift and Rotate Operations

```Markdown
| **Instruction**           | **Binary Form**                                                    |
|---------------------------|--------------------------------------------------------------------|
| `ROTR RD, RS, BITS5` (R2) | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | shamt: XXXXX | 000010 |
| `ROTRV RD, RS, RT`  (R2)  | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 000110        |
| `SLL RD, RS, SHIFT5`      | 000000 | 00000 | rt: XXXXX | rd: XXXXX | shamt: XXXXX | 000000     |
| `SLLV RD, RS, RT`         | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 000100        |
| `SRA RD, RS, SHIFT5`      | 000000 | 00000 | rt: XXXXX | rd: XXXXX | shamt: XXXXX | 000011     |
| `SRAV RD, RS, RT`         | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 000111        |
| `SRL RD, RS, SHIFT5`      | 000000 | 00000 | rt: XXXXX | rd: XXXXX | shamt: XXXXX | 000010     |
| `SRLV RD, RS, RT`         | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 000110        |
```

### Logical and BIT-Field Operations

```Markdown
| **Instruction**       | **Binary Form**                                                    |
|-----------------------|--------------------------------------------------------------------|
| `AND RD, RS, RT`      | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 100100        |
| `ANDI RD, RS, CONST16`| 001100 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX       |
| `EXT RT, RS, P, S`(R2)| 011111 | rs: XXXXX | rt: XXXXX | size: XXXXX | pos: XXXXX | 000000 |
| `INS RT, RS, P, S`(R2)| 011111 | rs: XXXXX | rt: XXXXX | size: XXXXX | pos: XXXXX | 000100 |
| `NOP`                 | Pseudo-instruction, translates to `SLL r0, r0, 0`                  |
| `NOR RD, RS, RT`      | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 100111        |
| `NOT RD, RS`          | Pseudo-instruction, translates to `NOR RD, RS, $zero`              |
| `OR RD, RS, RT`       | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 100101        |
| `ORI RD, RS, CONST16` | 001101 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX       |
| `WSBH RD, RS` (R2)    | 011111 | 00000 | rt: XXXXX | rd: XXXXX | 00010 | 100000            |
| `XOR RD, RS, RT`      | 000000 | rs: XXXXX | rt: XXXXX | rd: XXXXX | 00000 | 100110        |
| `XORI RD, RS, CONST16`| 001110 | rs: XXXXX | rt: XXXXX | immediate: XXXXXXXXXXXXXXXX       |
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

## Instruction Set Release 6

Notes:
- LWUPC, LDPC (load and store instructions) mentioned in Volume-I A but not found in volume-II A of MIPS Manual. Thus not included here.
- The term “unsigned” in ADDIU, ADDU is a misnomer; this operation is 32-bit modulo arithmetic that does not trap on 
overflow.

- Calculative Instructions:
  - ALU
  - Shift
  - Multiply and Divide
- Jumpy and Branch
  - PC-relative conditional branch
  - PC-region unconditional jump 
  - PC-relative unconditional branch 
    - Release 6 introduces unconditional branches with 26-bit offsets.
  - Absolute (register) unconditional jumps
    - Register-indirect jumps 
    - Register indexed jumps (Release 6)
  - Procedures
    - A set of procedure calls that record a return link address in a general register.
    - Procedure return is performed by register indirect jumps that use the contents of the link register, r31, as the branch target. This provides a hint to the hardware to adjust the call/return predictor appropriately.

### ALU Instructions

**16 Bit Operand:**

| **Instruction**       | op     | rs    | rt    | immediate        |
|-----------------------|--------|-------|-------|------------------|
| `ADDIU RD,RS, CONST16`| 001001 | XXXXX | XXXXX | XXXXXXXXXXXXXXXX |
| `ANDI RD, RS, CONST16`| 001100 | XXXXX | XXXXX | XXXXXXXXXXXXXXXX |
| `LUI RD, CONST16`     | 001111 | 00000 | XXXXX | XXXXXXXXXXXXXXXX |
| `ORI RD, RS, CONST16` | 001101 | XXXXX | XXXXX | XXXXXXXXXXXXXXXX |
| `SLTI RD, RS, CONST16`| 001010 | XXXXX | XXXXX | XXXXXXXXXXXXXXXX |
| `SLTIU RD,RS, CONST16`| 001011 | XXXXX | XXXXX | XXXXXXXXXXXXXXXX |
| `XORI RD, RS, CONST16`| 001110 | XXXXX | XXXXX | XXXXXXXXXXXXXXXX |

**3 Operands:**

| **Instruction**    | op     | rs    | rt    | rd    | blank | func   |
|--------------------|--------|-------|-------|-------|-------|--------|
| `ADD RD, RS, RT`   | 000000 | XXXXX | XXXXX | XXXXX | 00000 | 100000 |
| `ADDU RD, RS, RT`  | 000000 | XXXXX | XXXXX | XXXXX | 00000 | 100001 |
| `AND RD, RS, RT`   | 000000 | XXXXX | XXXXX | XXXXX | 00000 | 100100 |
| `NOR RD, RS, RT`   | 000000 | XXXXX | XXXXX | XXXXX | 00000 | 100111 |
| `OR RD, RS, RT`    | 000000 | XXXXX | XXXXX | XXXXX | 00000 | 100101 |
| `SLT RD, RS, RT`   | 000000 | XXXXX | XXXXX | XXXXX | 00000 | 101010 |
| `SLTU RD, RS, RT`  | 000000 | XXXXX | XXXXX | XXXXX | 00000 | 101011 |
| `SUB RD, RS, RT`   | 000000 | XXXXX | XXXXX | XXXXX | 00000 | 100010 |
| `SUBU RD, RS, RT`  | 000000 | XXXXX | XXXXX | XXXXX | 00000 | 100011 |
| `XOR RD, RS, RT`   | 000000 | XXXXX | XXXXX | XXXXX | 00000 | 100110 |

**2 Operands:**
| **Instruction**    | op     | rs    | blank | rd    | blank | func   |
|--------------------|--------|-------|-------|-------|-------|--------|
| `CLO RD, RS`       | 011100 | XXXXX | 00000 | XXXXX | 00000 | 100001 |
| `CLZ RD, RS`       | 011100 | XXXXX | 00000 | XXXXX | 00000 | 100000 |

### Shift Instructions

| **Instruction**       | op     | rs    | rt    | rd    | shamt | func   |
|-----------------------|--------|-------|-------|-------|-------|--------|
| `ALIGN ` |
| `BITSWAP` |
| `ROTR RD, RS, BITS5`  | 000000 | XXXXX | XXXXX | XXXXX | XXXXX | 000010 |
| `ROTRV RD, RS, RT`    | 000000 | XXXXX | XXXXX | XXXXX | 00000 | 000110 |
| `SLL RD, RS, SHIFT5`  | 000000 | 00000 | XXXXX | XXXXX | XXXXX | 000000 |
| `SLLV RD, RS, RT`     | 000000 | XXXXX | XXXXX | XXXXX | 00000 | 000100 |
| `SRA RD, RS, SHIFT5`  | 000000 | 00000 | XXXXX | XXXXX | XXXXX | 000011 |
| `SRAV RD, RS, RT`     | 000000 | XXXXX | XXXXX | XXXXX | 00000 | 000111 |
| `SRL RD, RS, SHIFT5`  | 000000 | 00000 | XXXXX | XXXXX | XXXXX | 000010 |
| `SRLV RD, RS, RT`     | 000000 | XXXXX | XXXXX | XXXXX | 00000 | 000110 |

### Multiple and Divide Instructions

| **Instruction**       |
|-----------------------|
| `MUL` |
| `MUH` |
| `MULU`|
| `MUHU`|
| `DMUL`|
| `DMUH`|
|`DMULU`|
|`DMUHU`|
| `DIV` |
| `MOD` |
| `DIVU`|
| `MODU`|
| `DDIV`|
| `DMOD`|
|`DDIVU`|
|`DMODU`|

### Jump and Branch Instructions

**Unconditional Jump 256-MB span:**

`J ADDR28`: 000010 and `JAL ADDR28`: 000011 with the 28 bit address after that.

**Unconditional Jump Absolute Address:**
| **Instruction**       | op     | rs    | blank | rd    | blank | func   |
|-----------------------|--------|-------|-------|-------|-------|--------|
| `JALR RD, RS`         | 000000 | XXXXX | 00000 | XXXXX | 00000 | 001001 |
| `JALR.HB RD, RS`      | 000000 | XXXXX | 00000 | XXXXX |

**PC-Relative Branch Instructions:**

| **Instruction**       | op     | rs    | rt    | offset             |
|-----------------------|--------|-------|-------|--------------------|
| `BEQ RS, RT, OFF18`   | 000100 | XXXXX | XXXXX | XXXXXXXXXXXXXXXXXX |
| `BNE RS, RT, OFF18`   | 000101 | XXXXX | XXXXX | XXXXXXXXXXXXXXXXXX |
| `BGEZ RS, OFF18`      | 000001 | XXXXX | 00001 | XXXXXXXXXXXXXXXXXX |
| `BGTZ RS, OFF18`      | 000111 | XXXXX | 00000 | XXXXXXXXXXXXXXXXXX |
| `BLEZ RS, OFF18`      | 000110 | XXXXX | 00000 | XXXXXXXXXXXXXXXXXX |
| `BLTZ RS, OFF18`      | 000001 | XXXXX | 00000 | XXXXXXXXXXXXXXXXXX |

**Unconditional Branch and Call:** Called as  `BC offset` or `BALC offset` with opcodes as  110010 and 111010 respectively. `offset` is 26 bits.

**Indexed Jumps (register + unscaled offset):** 

| Instruction       | pop           | Func         | rt    | offset  |
|-------------------|---------------|--------------|-------|---------|
| `JIC rt offset`   | POP66: 110110 | JIC  : 00000 | XXXXX | 16 bits |
| `JIALC rt offset` | POP76: 111110 | JIALC: 00000 | XXXXX | 16 bits |

**Compare to Zero Instructions:**

| Instruction | Description | Binary Form |
|-------------|-------------|-------------|
| BEQZC       | Compact Branch if Equal to Zero | `000001 sssss 00000 0000000000000001` |
| BNEZC       | Compact Branch if Not Equal to Zero | `000001 sssss 00001 0000000000000001` |
| BLEZC       | Compact Branch if Less Than or Equal to Zero | `000001 sssss 00010 0000000000000001` |
| BGEZC       | Compact Branch if Greater Than or Equal to Zero | `000001 sssss 00011 0000000000000001` |
| BGTZC       | Compact Branch if Greater Than Zero | `000001 sssss 00100 0000000000000001` |
| BLTZC       | Compact Branch if Less Than Zero | `000001 sssss 00101 0000000000000001` |

**Conditional Calls, Compare Against Zero:**

| Instruction | Description | Binary Form |
|-------------|-------------|-------------|
| BEQZALC     | Compact Branch if Equal to Zero, And Link | `000001 sssss 01000 0000000000000001` |
| BNEZALC     | Compact Branch if Not Equal to Zero, And Link | `000001 sssss 01001 0000000000000001` |
| BLEZALC     | Compact Branch if Less Than or Equal to Zero, And Link | `000001 sssss 01010 0000000000000001` |
| BGEZALC     | Compact Branch if Greater Than or Equal to Zero, And Link | `000001 sssss 01011 0000000000000001` |
| BGTZALC     | Compact Branch if Greater Than Zero, And Link | `000001 sssss 01100 0000000000000001` |
| BLTZALC     | Compact Branch if Less Than Zero, And Link | `000001 sssss 01101 0000000000000001` |

**Compare Equality (Register-Register):**

| Instruction | Description | Binary Form |
|-------------|-------------|-------------|
| BEQC        | Compact Branch if Equal | `000001 sssss ttttt 0000000000000001` |
| BNEC        | Compact Branch if Not Equal | `000001 sssss ttttt 0000000000000010` |

**Compare Signed (Register-Register):**

| Instruction | Description | Binary Form |
|-------------|-------------|-------------|
| BGEC        | Compact Branch if Greater than or Equal | `000001 sssss ttttt 0000000000000011` |
| BLTC        | Compact Branch if Less Than | `000001 sssss ttttt 0000000000000100` |

**Compare Unsigned (Register-Register):**

| Instruction | Description | Binary Form |
|-------------|-------------|-------------|
| BGEUC       | Compact Branch if Greater than or Equal, Unsigned | `000001 sssss ttttt 0000000000000101` |
| BLTUC       | Compact Branch if Less Than, Unsigned | `000001 sssss ttttt 0000000000000110` |

**Aliases Obtained by Reversing Operands:**

| Instruction | Description | Binary Form |
|-------------|-------------|-------------|
| BLEC        | Compact Branch if Less Than or Equal | `000001 sssss ttttt 0000000000000111` |
| BGTC        | Compact Branch if Greater Than | `000001 sssss ttttt 0000000000001000` |
| BLEUC       | Compact Branch if Less than or Equal, Unsigned | `000001 sssss ttttt 0000000000001001` |
| BGTUC       | Compact Branch if Greater Than, Unsigned | `000001 sssss ttttt 0000000000001010` |

**Branch if Overflow:**

| Instruction | Description | Binary Form |
|-------------|-------------|-------------|
| BOVC        | Compact Branch if Overflow (word) | `000001 sssss ttttt 0000000000001011` |
| BNVC        | Compact Branch if No overflow, word | `000001 sssss ttttt 0000000000001100` |

These binary forms are simplified representations and may vary based on the specific implementation and context. If you need more detailed or specific binary encodings, please refer to the MIPS32 Release 6 Instruction Set Manual.

### Address Computation and Large Constant Instructions 

| **Instruction**       |
|-----------------------|
| LSA |
| DLSA |
| AUI |
| DAUI |
| DAHI |
| DATI |
| ADDIUPC |
| AUIPC |
| ALUIPC |

Unsigned here is again a misnomer that signifies no overflow trap.

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
- 32 Floating Points Registers - `$f0` to `$31` - Used for floating point operations (Present on CP1)
- Special Registers
  - Progam Counter (PC) - Holds the address of next instruction to be executed
  - HI and LO Registers: Used to store the results of certain arithmetic operations like multiplication and division.
  - Cycle Counter Register: Often referred to as the Count register (`$count`), it keeps track of the number of cycles.

## Coprocessors

The main MIPS processors also has four coprocessors.
- cp0: System Control Coprocessor. Provides control, memory management, and exception handling functions. 
- cp1: Floating point Coprocessor.  Load and store instructions (move to and from coprocessor), reserved in the main opcode space. Coprocessor-specific operations, defined entirely by the coprocessor.
- cp2 - Seems to be for double operations
- cp3

## Branching

When executing a branch instruction, the very next instruction (called delay - slot instruction) comes in fetch because of pipelining. So...
- this delay slot instruction is typically executed. (Code optimization in compiler makes sure to move the branch instruction one line upward or backward depending on how you see it.)
- unless that instruction is a control transfer instruction. Pre-release 6 will give **UNPREDICTABLE** results, and release 6 will signal a Reserved Instruction Exception.
- Release 6  introduces conditional compact branches and compact jumps that do not have a delay slot; they have instead a forbidden slot. Release 6 unconditional compact branches have neither a delay slot nor a forbidden slot.
  - **FORBIDDEN:** any CTI, including branches and jumps, ERET, ERETNC, DERET, WAIT, and PAUSE.

# Memory Segments

- **Instruction Memory:** Memory map all the instructions to this segment. Address stored in program counter.
- **Data Segment:** Stores initialized global and static variables.
- **Block Started by Symbol (BSS) Segment:** Stores uninitialized global and static variables.
- **Heap:** Used for dynamic memory allocation.
- **Stack:** Used for function calls and local variables. Address stored at stack pointer (register 29)
- **Global Data Segment:** Stores global variables and constants. Address stored at global pointer (register 28)




# Plan

- Traditional model for implementing a processor does it in five stages: Fetch, Decode, Execute, Memory, and Write-back. This processor simulator however will only have one single stage. It will take instructions from memory and execute and store back in the same stage. This decision enables me to focus on the core concepts of the computer-architecture and enable better learning.
- We will have coprocessors cp0, and cp1 as extensions along with the processor in our simulator.

