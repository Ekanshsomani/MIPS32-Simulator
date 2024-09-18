# MIPS Processor Details

## Datapath and Control

- A simple clock edge triggered cycle. Four stages - fetch, decode, execute, memory. Each stage gets completed in one cycle irrelevant of the instrcution complexity.
- I will have 2 different channels that are an abstract way of implementing data and control bus on the simulator:
  - decode_channel
    - 32-bit instruction
    - control (2 bit): 
      - reserved_instruction (1 bit) (check yes if the next stage will try to execute a branch instruction in the next cycle)
      - actually_branching (1 bit) (will be yes if branch instruction actually led to a jump)
  - mem_channel
    - memory address (32 bit)
    - Control (8 bit)
      - read or write (1 bit)
      - width (2 bit) (how much to read or write)
      - regAddr (5 bit) (register to read from or write into)
- In each cycle, we execute the functions in following sequence:
  - Store or load if there is anything in the mem_channel
  - then execute if there is anything in the execute_channel. If a store/load instruction, push it on the mem_channel. If the instruction is branch and you do branch then check branching as yes in the execute channel, so that the next decoded instruction is discarded.
  - decode if there is anything on the decode channel. If the instruction is branch, check execute_branch as yes. So that the if the very next instruction turns out to be reserved, then we can signal the reserved exception.
  - fetch. Don't fetch if the execute_branch is set to yes in decode channel.
- Flushing out stages in reverse ensures that the channels are clear for the previous stage.

## Instruction Field Formats

- **R-Type:** op: 6 | rs: 5 | rt: 5 | rd: 5 | sa: 5 | func: 6 |
- **I-Type:**
  - op: 6 | rs: 5 | rt: 5 | immediate: 16 |
  - op: 6 | rd: 5 | offset: 21 |
  - op: 6 | offset: 26 |
  - op: 6 | rs: 5 | rt: 5 | rd: 5 | offset: 11 |
  - op: 6 | base: 5 | rt: 5 | offset: 10 | func: 6 |
- **J-Type:**
  - op: 6 | instr_index: 26 |

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

Instructions not mentioned in volume-I A but are there in release-6: SEB, SEH, EXT, INS, WSBH, MOVN, MOVZ

Notes:
- LWUPC, LDPC (load and store instructions) mentioned in Volume-I A but not found in volume-II A of MIPS Manual. Thus not included here.
- The term “unsigned” in ADDIU, ADDU is a misnomer; this operation is 32-bit modulo arithmetic that does not trap on overflow.

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

Below instructions are all of type: op (6 bit), rs (5 bit), rt(5 bit), immediate(16 bit)

| **Instruction**       | op     | op (in dec) |
|-----------------------|--------|----|
| `ADDIU RD,RS, CONST16`| 001001 | 9  |
| `ANDI RD, RS, CONST16`| 001100 | 12 |
| `ORI RD, RS, CONST16` | 001101 | 13 |
| `SLTI RD, RS, CONST16`| 001010 | 10 |
| `SLTIU RD,RS, CONST16`| 001011 | 11 |
| `XORI RD, RS, CONST16`| 001110 | 14 |

There is also suppose to be an LUI instruction above. But it is to be interpreted and done as AUI anyways so...

**3 Operands:**

Below instructions are all of type: op(6 bit) = 0, rs (5 bit), rt(5 bit), rd(5 bit), blank(5 bit) = 0, func(6 bit)

| **Instruction**    | func   | (in dec) |
|--------------------|--------|----------|
| `ADD RD, RS, RT`   | 100000 | 32 |
| `ADDU RD, RS, RT`  | 100001 | 33 |
| `AND RD, RS, RT`   | 100100 | 36 |
| `NOR RD, RS, RT`   | 100111 | 39 |
| `OR RD, RS, RT`    | 100101 | 37 |
| `SLT RD, RS, RT`   | 101010 | 42 |
| `SLTU RD, RS, RT`  | 101011 | 43 |
| `SUB RD, RS, RT`   | 100010 | 34 |
| `SUBU RD, RS, RT`  | 100011 | 35 |
| `XOR RD, RS, RT`   | 100110 | 38 |

**2 Operands:**

Below instructions are all of type: op(6 bit) = 28, rs (5 bit), blank(5 bit) = 0, rd(5 bit), blank(5 bit) = 0, func(6 bit)


| **Instruction**    | func   | (in dec) |
|--------------------|--------|----|
| `CLO RD, RS`       | 100001 | 33 |
| `CLZ RD, RS`       | 100000 | 32 |

### Shift Instructions

Below instructions are all of type: op(6 bit), rs/special (5 bit), blank(5 bit) = 0, rd(5 bit), shamt(5 bit), func(6 bit). First two have 31 as op code, the rest have zero.

| **Instruction** | rs/special  | rt    | rd    | shamt | func | func (in dec) |
|-----------------------|-------|-------|-------|-------|--------|----|
| `ALIGN RD, RS, RT, BP`| XXXXX | XXXXX | XXXXX | 010XX | 100000 | 32 |
| `BITSWAP RD, RT`      | 00000 | XXXXX | XXXXX | 00000 | 100000 | 32 |
| `ROTR RD, RS, BITS5`  | 00001 | XXXXX | XXXXX | XXXXX | 000010 | 2  |
| `SRL RD, RS, SHIFT5`  | 00000 | XXXXX | XXXXX | XXXXX | 000010 | 2  |
| `SLL RD, RS, SHIFT5`  | 00000 | XXXXX | XXXXX | XXXXX | 000000 | 0  |
| `SLLV RD, RS, RT`     | XXXXX | XXXXX | XXXXX | 00000 | 000100 | 4  |
| `SRA RD, RS, SHIFT5`  | 00000 | XXXXX | XXXXX | XXXXX | 000011 | 3  |
| `SRAV RD, RS, RT`     | XXXXX | XXXXX | XXXXX | 00000 | 000111 | 7  |
| `ROTRV RD, RS, RT`    | XXXXX | XXXXX | XXXXX | 00001 | 000110 | 6  |
| `SRLV RD, RS, RT`     | XXXXX | XXXXX | XXXXX | 00000 | 000110 | 6  |

### Multiple and Divide Instructions

Below instructions have binary of the form: op: 000000 | Rs: 5 | Rt: 5 | Rd: 5 | shamt: 5 | func: 6

| **Instruction**   | shamt | func   | shamt (in dec) | func (in dec) |
|-------------------|-------|--------|---|----|
| `MUL RD, RS, RT`  | 00010 | 011000 | 2 | 48 | 
| `MUH RD, RS, RT`  | 00011 | 011000 | 3 | 48 |
| `MULU RD, RS, RT` | 00010 | 011001 | 2 | 49 |
| `MUHU RD, RS, RT` | 00011 | 011001 | 3 | 49 |
| `DIV RD, RS, RT`  | 00010 | 011010 | 2 | 50 |
| `MOD RD, RS, RT`  | 00011 | 011010 | 3 | 50 |
| `DIVU RD, RS, RT` | 00010 | 011011 | 2 | 51 |
| `MODU RD, RS, RT` | 00011 | 011011 | 3 | 51 |


### Jump and Branch Instructions

**Unconditional Jump 256-MB span:** `J ADDR28`: 000010 (2) and `JAL ADDR28`: 000011 (3) with the 28 bit address after that.

**Unconditional Jump Absolute Address:** func in dec is 9.

| **Instruction**       | op     | rs    | blank | rd    | shamt | func   |
|-----------------------|--------|-------|-------|-------|-------|--------| 
| `JALR RD, RS`         | 000000 | XXXXX | 00000 | XXXXX | 0XXXX | 001001 |
| `JALR.HB RD, RS`      | 000000 | XXXXX | 00000 | XXXXX | 1XXXX | 001001 |

**PC-Relative Branch Instructions:** All are of the form op(6) | rs(5) | rt(5) | offset(16). First two have custom rt, last three have rt as zero, and the third one has rt as 1.

| **Instruction**       | op     | op(in dec) |
|-----------------------|--------|----|
| `BEQ RS, RT, OFF18`   | 000100 | 4 |
| `BNE RS, RT, OFF18`   | 000101 | 5 |
| `BGEZ RS, OFF18`      | 000001 | 1 |
| `BGTZ RS, OFF18`      | 000111 | 7 |
| `BLEZ RS, OFF18`      | 000110 | 6 |
| `BLTZ RS, OFF18`      | 000001 | 1 |

The below 3 don't have forbidden slot in the very next one, and won't cause a reserved instruction exception:

**Unconditional Branch and Call:** Called as  `BC offset` or `BALC offset` with opcodes as  110010 (50) and 111010 (58) respectively. `offset` is 26 bits.

**Indexed Jumps (register + unscaled offset):**  Both of them are of the form op(6) | 0(5) | rt(5) | offset(16).  `JIC rt offset`: 110110 (54) and `JIALC rt offset`: 111110 (62).

**Compare to Zero Instructions:**

BEQZC, BNEZC of the type op(6) | rs(5) | offset (21). The rest have rs and rt, and offset of length 16. A lot of transaction that end up translating to other in binary and work fine are not mentioned here. Since I won't have to simulate those.

| Instruction | op     | op(in dec) |
|-------------|--------|----|
| BEQZC       | 110110 | 54 |
| BNEZC       | 111110 | 62 |
| BEQC        | 001000 | 8  |
| BNEC        | 011000 | 24 |
| BLTC        | 010111 | 23 |
| BGEC        | 010110 | 22 |
| BLTUC       | 000111 | 7  |
| BGEUC       | 000110 | 6  |

**Conditional Calls, Compare Against Zero:**

Offset is 16 bits long in all the below instructions. And rt can never be zero.

| Instruction | op     | rs    | op(in dec) |
|-------------|--------|-------|----|
| BEQZALC     | 001000 | 00000 | 8  |
| BNEZALC     | 011000 | 00000 | 24 |
| BLEZALC     | 000110 | 00000 | 6  |
| BGEZALC     | 000110 | rt    | 6  |
| BGTZALC     | 000111 | 00000 | 7  |
| BLTZALC     | 000111 | rt    | 7  |

**Branch if Overflow:**

BOVC and BNVC have op-codes `001000`(8) and `011000`(24) respectively. They have rs, rt, and offset(16).

### Address Computation and Large Constant Instructions 

LSA has func `000101` at the end.

| **Instruction** | **Format**                  | op     | op (in dec) |
|-----------------|-----------------------------|--------|--------|
| LSA             | rs(5) rt(5) rd(5) 000 sa(2) | 000000 | 0  |
| AUI             | rs(5) rd(5) immediate(16)   | 001111 | 15 |
| ADDIUPC         | rs(5) 00 immediate(19)      | 111011 | 59 |
| AUIPC           | rs(5) 11110 immediate(16)   | 111011 | 59 |
| ALUIPC          | rs(5) 11111 immediate(16)   | 111011 | 59 |

Unsigned here is again a misnomer that signifies no overflow trap.

### Load and Store Instructions

Following instructions are of the format: op(6) | base(5) | rt(5) | offset(16).

| **inst** | **op** |
|------|----|
| LB   | 32 |
| LBU  | 36 |
| LH   | 33 |
| LHU  | 37 |
| LW   | 35 |
| SB   | 40 |
| SH   | 41 |

There are also lbe, lbue, lhe, lhue, lwe, sbe, swe. Which do the same thing but to and from user mode virtual address space when executing in kernel mode. So I have decided to leave them for now.

**Atomic read-modify-write**

LL - op(6) | base(5) rt(5) | offset(9) | 0 | func(6) - op = 31 and func = 54.
SC
LLWP


### Miscellaneous Instructions

**Serialization**

| **Instruction**       |
|-----------------------|
| SYNC | SPECIAL: 000000 | 15 zeros | stype: XXXXX | SYNC: 001111 |
| SYNCI | REGIMM: 000001 | BASE: XXXXX | SYNCI: 11111 | offset: 16 bit |

**Exception**

| **Instruction**       |
|-----------------------|
| BREAK | SPECIAL: 000000 | code: 20 bits | BREAK: 001101 |
| SYSCALL | SPECIAL: 000000 | code: 20 bits | SYSCALL: 001100 |

Each of the below instructions is called as something like `TEQ Rs Rt`. Binary from is: `SPECIAL: 000000 | rs: XXXXX | rt: XXXXX | code: 10 bits | func |`

| **Instruction** | **Func** |
|------|--------|
| TEQ  | 110100 |
| TGE  | 110000 |
| TGEU | 110001 |
| TLT  | 110010 |
| TLTU | 110100 |
| TNE  | 110100 |

**Conditional Move**

Assembly: `SELEQZ Rd, Rs, Rt` | Binary: `SPEICAL: 000000 | Rs: XXXXX | Rt: XXXXX | Rd: XXXXX | 00000| func`

| **Instruction** | **Func** |
|--------|--------|
| SELEQZ | 110101 |
| SELNEZ | 110111 |

**PREFETCH**

`PREF hint, offset (base)` :  SPECIAL3: 011111 | base: XXXXX | hint: XXXXX | offset: 9 bits | 0 | PREF: 110101 |
`NOP`: All zero
`SSNOP`: SHAMT: 1 (executes SLL)


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
- We will have coprocessor cp0 extension the simulator.
- 
Refs:
- https://ablconnect.harvard.edu/files/ablconnect/files/mips_instruction_set.pdf
- 