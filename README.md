# MIPS Processor Details

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

| **Instruction**       | op     | rs    | rt    | immediate        |
|-----------------------|--------|-------|-------|------------------|
| `ADDIU RD,RS, CONST16`| 001001 | XXXXX | XXXXX | XXXXXXXXXXXXXXXX |
| `ANDI RD, RS, CONST16`| 001100 | XXXXX | XXXXX | XXXXXXXXXXXXXXXX |
| `ORI RD, RS, CONST16` | 001101 | XXXXX | XXXXX | XXXXXXXXXXXXXXXX |
| `SLTI RD, RS, CONST16`| 001010 | XXXXX | XXXXX | XXXXXXXXXXXXXXXX |
| `SLTIU RD,RS, CONST16`| 001011 | XXXXX | XXXXX | XXXXXXXXXXXXXXXX |
| `XORI RD, RS, CONST16`| 001110 | XXXXX | XXXXX | XXXXXXXXXXXXXXXX |

There is also suppose to be an LUI instruction above. But it is to be interpreted and done as AUI anyways so...

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
| `ALIGN RD, RS, RT, BP`| 011111 | XXXXX | XXXXX | XXXXX | 010XX | 100000 |
| `BITSWAP RD, RT`      | 011111 | 00000 | XXXXX | XXXXX | 00000 | 100000 |
| `ROTR RD, RS, BITS5`  | 000000 | XXXXX | XXXXX | XXXXX | XXXXX | 000010 |
| `ROTRV RD, RS, RT`    | 000000 | XXXXX | XXXXX | XXXXX | 00000 | 000110 |
| `SLL RD, RS, SHIFT5`  | 000000 | 00000 | XXXXX | XXXXX | XXXXX | 000000 |
| `SLLV RD, RS, RT`     | 000000 | XXXXX | XXXXX | XXXXX | 00000 | 000100 |
| `SRA RD, RS, SHIFT5`  | 000000 | 00000 | XXXXX | XXXXX | XXXXX | 000011 |
| `SRAV RD, RS, RT`     | 000000 | XXXXX | XXXXX | XXXXX | 00000 | 000111 |
| `SRL RD, RS, SHIFT5`  | 000000 | 00000 | XXXXX | XXXXX | XXXXX | 000010 |
| `SRLV RD, RS, RT`     | 000000 | XXXXX | XXXXX | XXXXX | 00000 | 000110 |

### Multiple and Divide Instructions

Below instructions have binary of the form: SPECIAL: 000000 | Rs: 5 | Rt: 5 | Rd: 5 | func: 5 | sop: 6

| **Instruction**   | func  | sop    |
|-------------------|-------|--------|
| `MUL RD, RS, RT`  | 00010 | 011000 |
| `MUH RD, RS, RT`  | 00011 | 011000 |
| `MULU RD, RS, RT` | 00010 | 011001 |
| `MUHU RD, RS, RT` | 00011 | 011001 |
| `DIV RD, RS, RT`  | 00010 | 011010 |
| `MOD RD, RS, RT`  | 00011 | 011010 |
| `DIVU RD, RS, RT` | 00010 | 011011 |
| `MODU RD, RS, RT` | 00011 | 011011 |


### Jump and Branch Instructions

**Unconditional Jump 256-MB span:**

`J ADDR28`: 000010 and `JAL ADDR28`: 000011 with the 28 bit address after that.

**Unconditional Jump Absolute Address:**
| **Instruction**       | op     | rs    | blank | rd    | hint  | func   |
|-----------------------|--------|-------|-------|-------|-------|--------|
| `JALR RD, RS`         | 000000 | XXXXX | 00000 | XXXXX | XXXXX | 001001 |
| `JALR.HB RD, RS`      | 000000 | XXXXX | 00000 | XXXXX | 1XXXX | 001001 |

**PC-Relative Branch Instructions:**

| **Instruction**       | op     | rs    | rt    | offset             |
|-----------------------|--------|-------|-------|--------------------|
| `BEQ RS, RT, OFF18`   | 000100 | XXXXX | XXXXX | XXXXXXXXXXXXXXXXXX |
| `BNE RS, RT, OFF18`   | 000101 | XXXXX | XXXXX | XXXXXXXXXXXXXXXXXX |
| `BGEZ RS, OFF18`      | 000001 | XXXXX | 00001 | XXXXXXXXXXXXXXXXXX |
| `BGTZ RS, OFF18`      | 000111 | XXXXX | 00000 | XXXXXXXXXXXXXXXXXX |
| `BLEZ RS, OFF18`      | 000110 | XXXXX | 00000 | XXXXXXXXXXXXXXXXXX |
| `BLTZ RS, OFF18`      | 000001 | XXXXX | 00000 | XXXXXXXXXXXXXXXXXX |

The below 3 don't have forbidden slot in the very next one, and won't cause a reserved instruction exception:

**Unconditional Branch and Call:** Called as  `BC offset` or `BALC offset` with opcodes as  110010 and 111010 respectively. `offset` is 26 bits.

**Indexed Jumps (register + unscaled offset):** 

| Instruction       | pop           | Func         | rt    | offset  |
|-------------------|---------------|--------------|-------|---------|
| `JIC rt offset`   | POP66: 110110 | JIC  : 00000 | XXXXX | 16 bits |
| `JIALC rt offset` | POP76: 111110 | JIALC: 00000 | XXXXX | 16 bits |

**Compare to Zero Instructions:**

BEQZC, BNEZC of the type op(6) | rs(5) | offset (21). The rest have rs and rt, and offset of length 16. A lot of transaction that end up translating to other in binary and work fine are not mentioned here. Since I won't have to simulate those.

| Instruction | op     |
|-------------|--------|
| BEQZC       | 110110 |
| BNEZC       | 111110 |
| BEQC        | 001000 |
| BNEC        | 011000 |
| BLTC        | 010111 |
| BGEC        | 010110 |
| BLTUC       | 000111 |
| BGEUC       | 000110 |

**Conditional Calls, Compare Against Zero:**

Offset is 16 bits long in all the below instructions. And rt can never be zero.

| Instruction | op     | rs    |
|-------------|--------|-------|
| BEQZALC     | 001000 | 00000 |
| BNEZALC     | 011000 | 00000 |
| BLEZALC     | 000110 | 00000 | 
| BGEZALC     | 000110 | rt    |
| BGTZALC     | 000111 | 00000 |
| BLTZALC     | 000111 | rt    |

**Branch if Overflow:**

BOVC and BNVC have op-codes `001000` and `011000` respectively. They have rs, rt, and offset(16).

### Address Computation and Large Constant Instructions 

| **Instruction** | **Format**                  | op     | func   |
|-----------------|-----------------------------|--------|--------|
| LSA             | rs(5) rt(5) rd(5) 000 sa(2) | 000000 | 000101 |
| AUI             | rs(5) rd(5) immediate(16)   | 001111 ||
| ADDIUPC         | rs(5) 00 immediate(19)      | 111011 ||
| AUIPC           | rs(5) 11110 immediate(16)   | 111011 ||
| ALUIPC          | rs(5) 11111 immediate(16)   | 111011 ||

Unsigned here is again a misnomer that signifies no overflow trap.

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
- We will have coprocessors cp0, and cp1 as extensions along with the processor in our simulator.

- Instructions are:
  - I-Type: op(6) rs(5) rt(5) immediate(16)
  - J-Type: op(6) target(26)
  - R-type: op(6) rs(5) rt(5) rd(5) re(5) funct(6)
  

Refs:
- https://ablconnect.harvard.edu/files/ablconnect/files/mips_instruction_set.pdf
- 