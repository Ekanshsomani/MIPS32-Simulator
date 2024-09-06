#include <header.hpp>
#include <tuple>

// The pipeline executes backward from write back to fetch in each cycle
// so we can just not do fetch when we decode an instruction to find its jump or branch
// on to the next cycle we will do fetch after execution of jump and branch so everything is fine and dandy (yea!)

void J(uint32_t instr_index) { MIPS.PC = (0xF0000000 & MIPS.PC) | (instr_index << 2); }

// In the below two instructions, volume-II A says that control is returned to second instruction following the branch
// but I think that's before release-6, because back then the first instruction following branch was executed before the jump
void JAL(uint32_t instr_index) // this is deprecated in release-6
{
    MIPS.registers[MIPS.ra] = MIPS.PC;
    J(instr_index);
}

void JALR(regAddr& Rd, regAddr& Rs) // raise exception if target address is not 4-byte aligned
{
    MIPS.registers[Rd] = MIPS.PC;
    MIPS.PC = MIPS.registers[Rs];
}


void JALR_HB(regAddr& Rd, regAddr& Rs) 
{
    // yet to implement a software barrier that resolves all execution and instruction hazards 
    // created by Coprocessor 0 state changes
    JALR(Rd, Rs);
}

// currently we are adding the offset to address of the instruction following the branch (delay slot one)
// might have to change because of release-6 thing
void _B18(uint16_t& offset) // this is for use in this file only
{
    uint32_t isNeg = (0x8000 & offset) << 16;
    MIPS.PC = int32_t(MIPS.PC) + int32_t((uint32_t(0x7FFF & offset) << 2) | isNeg);
}

void BEQ(regAddr& Rs, regAddr& Rt, uint16_t& offset){ if(MIPS.registers[Rs] == MIPS.registers[Rt]) _B18(offset); }

void BNE(regAddr& Rs, regAddr& Rt, uint16_t& offset){ if(MIPS.registers[Rs] != MIPS.registers[Rt]) _B18(offset); }

void BGEZ(regAddr& Rs, uint16_t offset) { if(int32_t(MIPS.registers[Rs]) >= 0) _B18(offset); }

void BGTZ(regAddr& Rs, uint16_t offset) { if(int32_t(MIPS.registers[Rs]) > 0) _B18(offset); }

void BLEZ(regAddr& Rs, uint16_t offset) { if(int32_t(MIPS.registers[Rs]) <= 0) _B18(offset); }

void BLEZ(regAddr& Rs, uint16_t offset) { if(int32_t(MIPS.registers[Rs]) < 0) _B18(offset); }

// the below don't have a forbidden slot. No reserved instruction exception.
void BC(uint32_t offset) // this is _B28
{
    uint32_t isNeg = (0x2000000 & offset) << 6;
    MIPS.PC = int32_t(MIPS.PC) + int32_t((uint32_t(0x1FFFFFF & offset) << 2) | isNeg);
}

void BALC(uint32_t offset)
{
    MIPS.registers[MIPS.ra] = MIPS.PC;
    BC(offset);
}

void JIC(regAddr& Rt, uint16_t& offset){ MIPS.PC = MIPS.registers[Rt] + int32_t(int16_t(offset)); }

void JIALC(regAddr& Rt, uint16_t& offset)
{
    MIPS.registers[MIPS.ra] = MIPS.PC;
    JIC(Rt, offset);
}

void _B23(uint32_t offset)
{
    uint32_t isNeg = (0x100000 & offset) << 11;
    MIPS.PC = int32_t(MIPS.PC) + int32_t((uint32_t(0xFFFFF & offset) << 2) | isNeg);
}

void BEQC(regAddr& Rs, regAddr& Rt, uint16_t offset){ if(MIPS.registers[Rs] == MIPS.registers[Rt]) _B18(offset); }

void BNEC(regAddr& Rs, regAddr& Rt, uint16_t offset){ if(MIPS.registers[Rs] != MIPS.registers[Rt]) _B18(offset); }

void BLTC(regAddr& Rs, regAddr& Rt, uint16_t offset){ if(int32_t(MIPS.registers[Rs]) < int32_t(MIPS.registers[Rt])) _B18(offset); }

void BGEC(regAddr& Rs, regAddr& Rt, uint16_t offset){ if(int32_t(MIPS.registers[Rs]) >= int32_t(MIPS.registers[Rt])) _B18(offset); }

void BLTUC(regAddr& Rs, regAddr& Rt, uint16_t offset){ if(MIPS.registers[Rs] < MIPS.registers[Rt]) _B18(offset); }

void BGEUC(regAddr& Rs, regAddr& Rt, uint16_t offset){ if(MIPS.registers[Rs] >= MIPS.registers[Rt]) _B18(offset); } 

void BEQZC(regAddr& Rs, uint32_t offset){ if(MIPS.registers[Rs] == 0) _B23(offset); }

void BNEZC(regAddr& Rs, uint32_t offset){ if(MIPS.registers[Rs] != 0) _B23(offset); }

// Compact Zero-Compare and Branch-and-Link Instructions
void BEQZALC(regAddr& Rt, uint16_t offset){ if(MIPS.registers[Rt] == 0) _B18(offset); }

void BNEZALC(regAddr& Rt, uint16_t offset){ if(MIPS.registers[Rt] != 0) _B18(offset); }

void BLEZALC(regAddr& Rt, uint16_t offset){ if(MIPS.registers[Rt] <= 0) _B18(offset); }

void BGEZALC(regAddr& Rt, uint16_t offset){ if(MIPS.registers[Rt] >= 0) _B18(offset); }

void BGTZALC(regAddr& Rt, uint16_t offset){ if(MIPS.registers[Rt] > 0) _B18(offset); }

void BLTZALC(regAddr& Rt, uint16_t offset){ if(MIPS.registers[Rt] < 0) _B18(offset); }

// Branch depending on overflow

void BOVC(regAddr& Rs, regAddr& Rt, uint16_t offset)
    { if(__builtin_add_overflow(int32_t(MIPS.registers[Rs]), int32_t(MIPS.registers[Rt]), &ignore)) _B18(offset); } // ignore is from the tuple library.

void BNVC(regAddr& Rs, regAddr& Rt, uint16_t offset)
    { if(not __builtin_add_overflow(int32_t(MIPS.registers[Rs]), int32_t(MIPS.registers[Rt]), &ignore)) _B18(offset); }

