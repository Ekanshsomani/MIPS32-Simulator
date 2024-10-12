#include <funcs.hpp>
#include <tuple>

void J(const uint32_t& instr_index) { mips.PC = (0xF0000000 & mips.PC) | (instr_index << 2); }

// In the below two instructions, volume-II A says that control is returned to second instruction following the branch
// but I think that's before release-6, because back then the first instruction following branch was executed before the jump
void JAL(const uint32_t& instr_index) // this is deprecated in release-6
{
    mips.registers[mips.ra] = mips.PC;
    J(instr_index);
}

void JALR(regAddr& Rd, regAddr& Rs) // raise exception if target address is not 4-byte aligned
{
    mips.registers[Rd] = mips.PC;
    mips.PC = mips.registers[Rs];
}


void JALR_HB(regAddr& Rd, regAddr& Rs)
{
    // yet to implement a software barrier that resolves all execution and instruction hazards 
    // created by Coprocessor 0 state changes
    JALR(Rd, Rs);
}

// currently we are adding the offset to address of the instruction following the
//  branch (delay slot one)
void _B18(const uint16_t& offset) // this is for use in this file only
{
    uint32_t isNeg = (0x8000 & offset) << 16;
    mips.PC = int32_t(mips.PC) + int32_t((uint32_t(0x7FFF & offset) << 2) | isNeg);
}

void BEQ(regAddr& Rs, regAddr& Rt, const uint16_t& offset){ if(mips.registers[Rs] == mips.registers[Rt]) _B18(offset); }

void BNE(regAddr& Rs, regAddr& Rt, const uint16_t& offset){ if(mips.registers[Rs] != mips.registers[Rt]) _B18(offset); }

void BGEZ(regAddr& Rs, const uint16_t& offset) { if(int32_t(mips.registers[Rs]) >= 0) _B18(offset); }

void BGTZ(regAddr& Rs, const uint16_t& offset) { if(int32_t(mips.registers[Rs]) > 0) _B18(offset); }

void BLEZ(regAddr& Rs, const uint16_t& offset) { if(int32_t(mips.registers[Rs]) <= 0) _B18(offset); }

void BLTZ(regAddr& Rs, const uint16_t& offset) { if(int32_t(mips.registers[Rs]) < 0) _B18(offset); }

// the below don't have a forbidden slot. No reserved instruction exception.
void BC(const uint32_t& offset) // this is _B28
{
    uint32_t isNeg = (0x2000000 & offset) << 6;
    mips.PC = int32_t(mips.PC) + int32_t((uint32_t(0x1FFFFFF & offset) << 2) | isNeg);
}

void BALC(const uint32_t& offset)
{
    mips.registers[mips.ra] = mips.PC;
    BC(offset);
}

void JIC(regAddr& Rt, uint16_t& offset){ mips.PC = mips.registers[Rt] + int32_t(int16_t(offset)); }

void JIALC(regAddr& Rt, uint16_t& offset)
{
    mips.registers[mips.ra] = mips.PC;
    JIC(Rt, offset);
}

void _B23(const uint32_t& offset)
{
    uint32_t isNeg = (0x100000 & offset) << 11;
    mips.PC = int32_t(mips.PC) + int32_t((uint32_t(0xFFFFF & offset) << 2) | isNeg);
}

void BEQC(regAddr& Rs, regAddr& Rt, const uint16_t& offset){ if(mips.registers[Rs] == mips.registers[Rt]) _B18(offset); }

void BNEC(regAddr& Rs, regAddr& Rt, const uint16_t& offset){ if(mips.registers[Rs] != mips.registers[Rt]) _B18(offset); }

void BLTC(regAddr& Rs, regAddr& Rt, const uint16_t& offset){ if(int32_t(mips.registers[Rs]) < int32_t(mips.registers[Rt])) _B18(offset); }

void BGEC(regAddr& Rs, regAddr& Rt, const uint16_t& offset){ if(int32_t(mips.registers[Rs]) >= int32_t(mips.registers[Rt])) _B18(offset); }

void BLTUC(regAddr& Rs, regAddr& Rt, const uint16_t& offset){ if(mips.registers[Rs] < mips.registers[Rt]) _B18(offset); }

void BGEUC(regAddr& Rs, regAddr& Rt, const uint16_t& offset){ if(mips.registers[Rs] >= mips.registers[Rt]) _B18(offset); } 

void BEQZC(regAddr& Rs, const uint32_t& offset){ if(mips.registers[Rs] == 0) _B23(offset); }

void BNEZC(regAddr& Rs, const uint32_t& offset){ if(mips.registers[Rs] != 0) _B23(offset); }

// Compact Zero-Compare and Branch-and-Link Instructions
void BEQZALC(regAddr& Rt, const uint16_t& offset){ if(mips.registers[Rt] == 0) _B18(offset); }

void BNEZALC(regAddr& Rt, const uint16_t& offset){ if(mips.registers[Rt] != 0) _B18(offset); }

void BLEZALC(regAddr& Rt, const uint16_t& offset){ if(mips.registers[Rt] <= 0) _B18(offset); }

void BGEZALC(regAddr& Rt, const uint16_t& offset){ if(mips.registers[Rt] >= 0) _B18(offset); }

void BGTZALC(regAddr& Rt, const uint16_t& offset){ if(mips.registers[Rt] > 0) _B18(offset); }

void BLTZALC(regAddr& Rt, const uint16_t& offset){ if(mips.registers[Rt] < 0) _B18(offset); }

// Branch depending on overflow

void BOVC(regAddr& Rs, regAddr& Rt, const uint16_t& offset)
    { if(__builtin_add_overflow(int32_t(mips.registers[Rs]), int32_t(mips.registers[Rt]), &ignore)) _B18(offset); } // ignore is from the tuple library.

void BNVC(regAddr& Rs, regAddr& Rt, const uint16_t& offset)
    { if(not __builtin_add_overflow(int32_t(mips.registers[Rs]), int32_t(mips.registers[Rt]), &ignore)) _B18(offset); }

