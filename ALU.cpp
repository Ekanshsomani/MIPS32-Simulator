#include <funcs.hpp>

// Arithmetic Instructions

void ADD(regAddr& Rd, regAddr& Rs, regAddr& Rt) // yet to add overflow trap
{
    mips.registers[Rd] = static_cast<int32_t>(mips.registers[Rs]) + static_cast<int32_t>(mips.registers[Rt]);
}

void ADDI(regAddr& Rd, regAddr& Rs, const uint16_t& const16) // yet to add overflow trap
{
    int32_t a = static_cast<int32_t>(mips.registers[Rs]);
    int32_t b = static_cast<int16_t>(const16); // implicit casting will do sign extension after static cast
    int32_t c = a+b;

    mips.registers[Rd] = static_cast<uint32_t>(c);
}

// term unsigned in below two functions is a misnomer. It means no overflow traps.
void ADDIU(regAddr& Rd, regAddr& Rs, const uint16_t& const16) { mips.registers[Rd] = static_cast<int32_t>(const16) + static_cast<int32_t>(mips.registers[Rs]); }

void ADDU(regAddr& Rd, regAddr& Rs, regAddr& Rt) { mips.registers[Rd] = static_cast<int32_t>(mips.registers[Rs]) + static_cast<int32_t>(mips.registers[Rt]); }

void CLO(regAddr& Rd, regAddr& Rs) { mips.registers[Rd] = __builtin_clz(~( mips.registers[Rs])); }

void CLZ(regAddr& Rd, regAddr& Rs) { mips.registers[Rd] = __builtin_clz(mips.registers[Rs]); }

void SEB(regAddr& Rd, regAddr& Rs)
{ 
    mips.registers[Rd] = static_cast<uint32_t>(int32_t(
        static_cast<int8_t>(mips.registers[Rs])
    ));
}

void SEH(regAddr& Rd, regAddr& Rs)
{
    mips.registers[Rd] = static_cast<uint32_t>(int32_t(
        static_cast<int16_t>(mips.registers[Rs])
    ));
}

void SUB(regAddr& Rd, regAddr& Rs, regAddr& Rt) // yet to add overflow trap
{
    mips.registers[Rd] = static_cast<int32_t>(mips.registers[Rs]) - static_cast<int32_t>(mips.registers[Rt]);
}

void SUBU(regAddr& Rd, regAddr& Rs, regAddr& Rt) { mips.registers[Rd] = static_cast<int32_t>(mips.registers[Rs]) - static_cast<int32_t>(mips.registers[Rt]); }

// SHIFT Instructions

void ROTR(regAddr& Rd, regAddr& Rs, regAddr& bits5)
{
    uint32_t a = MIPS.registers[Rs];
    mips.registers[Rd] = (a >> bits5) | (a << (32 - bits5));
}

void ROTRV(regAddr& Rd, regAddr& Rs, regAddr& Rt) { ROTR(Rd, Rs, static_cast<uint8_t>(mips.registers[Rt]) & 0x1F); }

void SLL(regAddr& Rd, regAddr& Rs, regAddr& shift5) { mips.registers[Rd] = mips.registers[Rs] << shift5; }

void SLLV(regAddr& Rd, regAddr& Rs, regAddr& Rt) { SLL(Rd, Rs, static_cast<uint8_t>(mips.registers[Rt]) & 0x1F); }

void SRA(regAddr& Rd, regAddr& Rs, regAddr& shift5)
{
    uint32_t a = MIPS.registers[Rs];
    bool msb = a & 0x80000000;

    mips.registers[Rd] = a >> shift5;

    if(msb) mips.registers[Rd] |= (0xFFFFFFFF << (32 - shift5));
}

void SRAV(regAddr& Rd, regAddr& Rs, regAddr& Rt) { SRA(Rd, Rs, static_cast<uint8_t>(mips.registers[Rt]) & 0x1F); }

void SRL(regAddr& Rd, regAddr& Rs, regAddr& shift5) { mips.registers[Rd] = mips.registers[Rs] >> shift5; }

void SRLV(regAddr& Rd, regAddr& Rs, regAddr& Rt) { SRL(Rd, Rs, static_cast<uint8_t>(mips.registers[Rt]) & 0x1F); }

// Logic Instructions

void AND(regAddr& Rd, regAddr& Rs, regAddr& Rt) { mips.registers[Rd] = mips.registers[Rs] & mips.registers[Rt]; }

void ANDI(regAddr& Rd, regAddr& Rs, const uint16_t& const16) { mips.registers[Rd] = mips.registers[Rs] & const16; }

void EXT(regAddr& Rt, regAddr& Rs, regAddr& pos, regAddr& size)
{
    mips.registers[Rt] = ((1ULL << size) - 1) & (mips.registers[Rs] >> pos);
}

void INS(regAddr& Rt, regAddr& Rs, regAddr& pos, regAddr& size)
{
    uint32_t mask = (1ULL << size) - 1;
    mips.registers[Rt] = (mips.registers[Rt] & ~(mask << pos)) | ((mask & mips.registers[Rs]) << pos);
}

void NOR(regAddr& Rd, regAddr& Rs, regAddr& Rt) { mips.registers[Rd] = ~(mips.registers[Rs] | mips.registers[Rt]); }

void OR(regAddr& Rd, regAddr& Rs, regAddr& Rt) { mips.registers[Rd] = mips.registers[Rs] | mips.registers[Rt]; }

void ORI(regAddr& Rd, regAddr& Rs, const uint16_t& const16){ mips.registers[Rd] = mips.registers[Rs] | const16; }

void WSBH(regAddr& Rd, regAddr& Rs)
{
    uint32_t oprnd = MIPS.registers[Rs];

    mips.registers[Rd] = 
        ((oprnd & 0xFF000000) >> 8) |
        ((oprnd & 0x00FF0000) << 8) |
        ((oprnd & 0x0000FF00) >> 8) |
        ((oprnd & 0x000000FF) << 8);

}

void XOR(regAddr& Rd, regAddr& Rs, regAddr& Rt) { mips.registers[Rd] = mips.registers[Rs] ^ mips.registers[Rt]; }

void XORI(regAddr& Rd, regAddr& Rs, const uint16_t& const16){ mips.registers[Rd] = mips.registers[Rs] ^ const16; }

void MOVN(regAddr& Rd, regAddr& Rs, regAddr& Rt) { if(mips.registers[Rt]) mips.registers[Rd] = mips.registers[Rs]; }

void MOVZ(regAddr& Rd, regAddr& Rs, regAddr& Rt) { if(not mips.registers[Rt]) mips.registers[Rd] = mips.registers[Rs]; }

void SLT(regAddr& Rd, regAddr& Rs, regAddr& Rt) // yet to add overflow trap
{
    int32_t a = static_cast<int32_t>(mips.registers[Rs]);
    int32_t b = static_cast<int32_t>(mips.registers[Rt]);

    mips.registers[Rd] = (a < b) ? 1 : 0;
}

void SLTI(regAddr& Rd, regAddr& Rs, const uint16_t& const16) // yet to add overflow trap
{
    int32_t a = static_cast<int32_t>(mips.registers[Rs]);
    int32_t b = static_cast<int16_t>(const16); // implicit casting will do sign extension after static cast

    mips.registers[Rd] = (a < b) ? 1 : 0;
}

void SLTIU(regAddr& Rd, regAddr& Rs, const uint16_t& const16) { mips.registers[Rd] = (mips.registers[Rs] < (int32_t(const16))) ? 1 : 0; }

void SLTU(regAddr& Rd, regAddr& Rs, regAddr& Rt) 
    { mips.registers[Rd] = (static_cast<int32_t>(mips.registers[Rs]) < static_cast<int32_t>(mips.registers[Rt])) ? 1 : 0; }

void ALIGN(regAddr& Rd, regAddr& Rs, regAddr& Rt, regAddr& bp) 
    { mips.registers[Rd] = (mips.registers[Rs] << (8*bp)) | (mips.registers[Rt] >> ((4 - bp) * 8)); }

void BITSWAP(regAddr& Rd, regAddr& Rt)
{
    uint32_t oprnd = MIPS.registers[Rt];
    uint32_t &ans = mips.registers[Rd];
    ans = 0;

    uint32_t byteArr[4] {0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF};
    uint32_t op = 0x000000FF;

    for(int i = 0; i < 4; i++)
    {
        uint8_t extracted = (0xFF000000 & oprnd);
        uint8_t reversed {0};
        ans <<= 8;
        oprnd <<= 8;

        for(int j = 0; j < 8; j++)
        {
            reversed <<= 1;
            reversed |= (extracted & 1);
            extracted >>= 1;
        }
        
        ans |= reversed;
    }
}

// Multiply and Divide Instructions

void MUL(regAddr& Rd, regAddr& Rs, regAddr& Rt)
{
    int64_t a = static_cast<int32_t>(mips.registers[Rs]);
    int64_t b = static_cast<int32_t>(mips.registers[Rt]);
    
    mips.registers[Rd] = ((a * b) & 0xFFFFFFFF);
}

void MUH(regAddr& Rd, regAddr& Rs, regAddr& Rt)
{
    int64_t a = static_cast<int32_t>(mips.registers[Rs]);
    int64_t b = static_cast<int32_t>(mips.registers[Rt]);

    mips.registers[Rd] = ((a * b) >> 32);
}

void MULU(regAddr& Rd, regAddr& Rs, regAddr& Rt)
    { mips.registers[Rd] = ((uint64_t(mips.registers[Rs]) * uint64_t(mips.registers[Rt])) & 0xFFFFFFFF); }

void MUHU(regAddr& Rd, regAddr& Rs, regAddr& Rt)
    { mips.registers[Rd] = ((uint64_t(mips.registers[Rs]) * uint64_t(mips.registers[Rt])) >> 32); }

// the program currently stops if value at Rt is zero and raises an exception. I need to change it so that it keeps executing.
// probably change the action to continue in the error specification there.

void DIV(regAddr& Rd, regAddr& Rs, regAddr& Rt)
    { mips.registers[Rd] = static_cast<int32_t>(mips.registers[Rs]) / static_cast<int32_t>(mips.registers[Rt]); }

void MOD(regAddr& Rd, regAddr& Rs, regAddr& Rt)
    { mips.registers[Rd] = static_cast<int32_t>(mips.registers[Rs]) % static_cast<int32_t>(mips.registers[Rt]); }

void DIVU(regAddr& Rd, regAddr& Rs, regAddr& Rt)
    { mips.registers[Rd] = mips.registers[Rs] / mips.registers[Rt]; }

void MODU(regAddr& Rd, regAddr& Rs, regAddr& Rt)
    { mips.registers[Rd] = mips.registers[Rs] % mips.registers[Rt]; }


// Address Computation and Large Constant

void LSA(regAddr& Rd, regAddr& Rs, regAddr& Rt, regAddr& sa)
    { mips.registers[Rd] = (mips.registers[Rs] << (sa + 1)) + mips.registers[Rt]; }

void AUI(regAddr& Rd, regAddr& Rs, const uint16_t& immediate)
    { mips.registers[Rd] = int32_t(mips.registers[Rs]) + int32_t(uint32_t(immediate) << 16); }

// the below instructions are based on the hope that pc has moved on sequentially in each fetch after fetching this instruction
// if not, and some villian can make it jump before this instruction is completed, then you need to save the code.

void ADDIUPC(regAddr& Rd, const uint32_t& immediate)
{
    uint32_t isNeg = immediate & 0x40000;
    mips.registers[Rd] = mips.PC - 8 + (((immediate & 0x3FFFF) << 2) | isNeg);
}

// its details in manual only says add to pc (i'm assuming that manual doesn't imply two different pc's between ADDIUPC
// and these two)
void ALUIPC(regAddr& Rd, const uint16_t& immediate)
    {mips.registers[Rd] = (mips.PC - 8 + int32_t(uint32_t(immediate) << 16)) & 0xFFFF0000;}

void AUIPC(regAddr& Rd, const uint16_t& immediate)
    {mips.registers[Rd] = mips.PC - 8 + int32_t(uint32_t(immediate) << 16);}

// two miscellaneous instructions (weirdly simple)
void SELNEZ(regAddr& Rd, regAddr& Rs, regAddr& Rt){ if(mips.registers[Rt]) mips.registers[Rd] = mips.registers[Rs]; }

void SELEQZ(regAddr& Rd, regAddr& Rs, regAddr& Rt){ if(not mips.registers[Rt]) mips.registers[Rd] = mips.registers[Rs]; }

// load and store instructions
void LB(regAddr& Rt, regAddr& base, const uint16_t& offset)
{
    mips.mem_channel.data = mips.registers[base] + int16_t(offset);
    mips.mem_channel.control = (0 << 5) | Rt;
    mips.mem_channel.addit = 0;
}

void LBU(regAddr& Rt, regAddr& base, const uint16_t& offset)
{
    mips.mem_channel.data = mips.registers[base] + int16_t(offset);
    mips.mem_channel.control = (0 << 5) | Rt;
    mips.mem_channel.addit = 1;
}

void LH(regAddr& Rt, regAddr& base, const uint16_t& offset)
{
    mips.mem_channel.data = mips.registers[base] + int16_t(offset);
    mips.mem_channel.control = (1 << 5) | Rt;
    mips.mem_channel.addit = 0;
}

void LHU(regAddr& Rt, regAddr& base, const uint16_t& offset)
{
    mips.mem_channel.data = mips.registers[base] + int16_t(offset);
    mips.mem_channel.control = (1 << 5) | Rt;
    mips.mem_channel.addit = 1;
}

void LW(regAddr& Rt, regAddr& base, const uint16_t& offset)
{
    mips.mem_channel.data = mips.registers[base] + int16_t(offset);
    mips.mem_channel.control = (3 << 5) | Rt;
    mips.mem_channel.addit = 0;
}

void SB(regAddr& Rt, regAddr& base, const uint16_t& offset)
{
    mips.mem_channel.data = mips.registers[base] + int16_t(offset);
    mips.mem_channel.control = (1 << 7) | (0 << 5) | Rt;
}

void SH(regAddr& Rt, regAddr& base, const uint16_t& offset)
{
    mips.mem_channel.data = mips.registers[base] + int16_t(offset);
    mips.mem_channel.control = (1 << 7) | (1 << 5) | Rt;
}

void SW(regAddr& Rt, regAddr& base, const uint16_t& offset)
{
    mips.mem_channel.data = mips.registers[base] + int16_t(offset);
    mips.mem_channel.control = (1 << 7) | (3 << 5) | Rt;
}