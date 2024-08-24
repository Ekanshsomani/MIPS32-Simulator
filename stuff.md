My Plan to create the MIPS Processor Simulator.

I can use github repo: [91varunsharma/MIPS-Simulator](https://github.com/91varunsharma/MIPS-Simulator/) as reference. The code there is simple and clear. But the idea is to try to make as much of it as possible by just relying on docs and stuff.

Some possibly useful stuff (for later):
- https://spimsimulator.sourceforge.net/

### 1. **Understand the Instruction Set Architecture (ISA)**

I am going forward with 32-bits MIPS processor. 

- It has 68 registers.
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
- The 32 bit instruction code can be divided:
  - First 6 bits will always be the opcode. The rest of division should be done on the basis of this.
  - Instruction Formats.
    - R: op(6) rs(5) rt(5) rd(5) shamt(5) funct(6)
    - I: op(6) rs(5) rt(5) immediate(16)
    - J: op(6) target address(26)
  - J-Format Instruction Addressing
    - 26-bit Target Address: The J-format instruction contains a 26-bit target address field.
    - Shift Left by 2 Bits: This 26-bit address is shifted left by 2 bits, effectively adding two zeros at the end. This makes it a 28-bit address.
    - Concatenate with PC: The remaining 4 bits are taken from the most significant bits (MSBs) of the Program Counter (PC). These 4 bits are the upper bits of the address of the instruction following the jump.
  - R-format usage of the 16-bit Immediate Value
    - Immediate Operand: For arithmetic and logical operations (e.g., ADDI, ANDI), the 16-bit immediate value is sign-extended to 32 bits.
    - Branch Target Offset: For branch instructions (e.g., BEQ, BNE), the 16-bit immediate value is sign-extended, shifted left by 2 bits, and added to the Program Counter (PC) to form the branch target address.
    - Memory Addressing: For load and store instructions (e.g., LW, SW), the 16-bit immediate value is sign-extended and added to the base address in the register to form the effective memory address.
  - Refs:
    - [Best I found](https://www.cs.kzoo.edu/cs230/Resources/MIPS/MachineXL/InstructionFormats.html)
    - [Encoding MIPS Instructions](https://www.dcc.fc.up.pt/~ricroc/aulas/1920/ac/apontamentos/P04_encoding_mips_instructions.pdf)
    - [MIPS Green Sheet](https://courses.cs.washington.edu/courses/cse378/09au/MIPS_Green_Sheet.pdf)


(1) MIPS Assembly - University of the Pacific. https://ecs-network.serv.pacific.edu/ecpe-170/tutorials/tutorials_index/16mipsassembly.pdf.
(2) Getting Started with MIPS Instructions Set Simulator - Microcontrollers Lab. https://microcontrollerslab.com/pcspim-tutorial-mips-simulator/.
(3) GitHub - imtavin/MIPS-Processor-Simulator: The MIPS Processor Simulator .... https://github.com/imtavin/MIPS-Processor-Simulator.
(4) Multi Cycle Microarchitecture MIPS Processor - GitHub. https://github.com/Elzawawy/mips-processor-simulator/blob/master/multi-cycle/README.md.
(5) MR MIPS Simulator by Misterm. https://misterm.itch.io/mr-mips-simulator.
(6) undefined. http://www.cs.wisc.edu/~larus/SPIM/pcspim.zip.

Toally Unrelated but SOO good: https://www.eecs.harvard.edu/~cs161/notes/mips-part-I.pdf.
This is how presentations should be made.