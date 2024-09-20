#include <funcs.hpp>

using namespace std;

// Arithmetic Instructions

void ADD(regAddr& Rd, regAddr& Rs, regAddr& Rt) // yet to add overflow trap
{
    MIPS.registers[Rd] = static_cast<int32_t>(MIPS.registers[Rs]) + static_cast<int32_t>(MIPS.registers[Rt]);
}

void ADDI(regAddr& Rd, regAddr& Rs, uint16_t const16) // yet to add overflow trap
{
    int32_t a = static_cast<int32_t>(MIPS.registers[Rs]);
    int32_t b = static_cast<int16_t>(const16); // implicit casting will do sign extension after static cast
    int32_t c = a+b;

    MIPS.registers[Rd] = static_cast<uint32_t>(c);
}

// term unsigned in below two functions is a misnomer. It means no overflow traps.
void ADDIU(regAddr& Rd, regAddr& Rs, uint16_t const16) { MIPS.registers[Rd] = static_cast<int32_t>(const16) + static_cast<int32_t>(MIPS.registers[Rs]); }

void ADDU(regAddr& Rd, regAddr& Rs, uint32_t Rt) { MIPS.registers[Rd] = static_cast<int32_t>(MIPS.registers[Rs]) + static_cast<int32_t>(MIPS.registers[Rt]); }

void CLO(regAddr& Rd, regAddr& Rs) { MIPS.registers[Rd] = __builtin_clz(~( MIPS.registers[Rs])); }

void CLZ(regAddr& Rd, regAddr& Rs) { MIPS.registers[Rd] = __builtin_clz(MIPS.registers[Rs]); }

void SEB(regAddr& Rd, regAddr& Rs)
{ 
    MIPS.registers[Rd] = static_cast<uint32_t>(int32_t(
        static_cast<int8_t>(MIPS.registers[Rs])
    ));
}

void SEH(regAddr& Rd, regAddr& Rs)
{
    MIPS.registers[Rd] = static_cast<uint32_t>(int32_t(
        static_cast<int16_t>(MIPS.registers[Rs])
    ));
}

void SUB(regAddr& Rd, regAddr& Rs, regAddr& Rt) // yet to add overflow trap
{
    MIPS.registers[Rd] = static_cast<int32_t>(MIPS.registers[Rs]) - static_cast<int32_t>(MIPS.registers[Rt]);
}

void SUBU(regAddr& Rd, regAddr& Rs, regAddr& Rt) { MIPS.registers[Rd] = static_cast<int32_t>(MIPS.registers[Rs]) - static_cast<int32_t>(MIPS.registers[Rt]); }

// SHIFT Instructions

void ROTR(regAddr& Rd, regAddr& Rs, regAddr& bits5)
{
    uint32_t a = MIPS.registers[Rs];
    MIPS.registers[Rd] = (a >> bits5) | (a << (32 - bits5));
}

void ROTRV(regAddr& Rd, regAddr& Rs, regAddr& Rt) { ROTR(Rd, Rs, static_cast<uint8_t>(MIPS.registers[Rt]) & 0x1F); }

void SLL(regAddr& Rd, regAddr& Rs, regAddr& shift5) { MIPS.registers[Rd] = MIPS.registers[Rs] << shift5; }

void SLLV(regAddr& Rd, regAddr& Rs, regAddr& Rt) { SLL(Rd, Rs, static_cast<uint8_t>(MIPS.registers[Rt]) & 0x1F); }

void SRA(regAddr& Rd, regAddr& Rs, regAddr& shift5)
{
    uint32_t a = MIPS.registers[Rs];
    bool msb = a & 0x80000000;

    MIPS.registers[Rd] = a >> shift5;

    if(msb) MIPS.registers[Rd] |= (0xFFFFFFFF << (32 - shift5));
}

void SRAV(regAddr& Rd, regAddr& Rs, regAddr& Rt) { SRA(Rd, Rs, static_cast<uint8_t>(MIPS.registers[Rt]) & 0x1F); }

void SRL(regAddr& Rd, regAddr& Rs, regAddr& shift5) { MIPS.registers[Rd] = MIPS.registers[Rs] >> shift5; }

void SRLV(regAddr& Rd, regAddr& Rs, regAddr& Rt) { SRL(Rd, Rs, static_cast<uint8_t>(MIPS.registers[Rt]) & 0x1F); }

// Logic Instructions

void AND(regAddr& Rd, regAddr& Rs, regAddr& Rt) { MIPS.registers[Rd] = MIPS.registers[Rs] & MIPS.registers[Rt]; }

void ANDI(regAddr& Rd, regAddr& Rs, uint16_t const16) { MIPS.registers[Rd] = MIPS.registers[Rs] & const16; }

void EXT(regAddr& Rt, regAddr& Rs, regAddr& pos, regAddr& size)
{
    MIPS.registers[Rt] = ((1ULL << size) - 1) & (MIPS.registers[Rs] >> pos);
}

void INS(regAddr& Rt, regAddr& Rs, regAddr& pos, regAddr& size)
{
    uint32_t mask = (1ULL << size) - 1;
    MIPS.registers[Rt] = (MIPS.registers[Rt] & ~(mask << pos)) | ((mask & MIPS.registers[Rs]) << pos);
}

void NOR(regAddr& Rd, regAddr& Rs, regAddr& Rt) { MIPS.registers[Rd] = ~(MIPS.registers[Rs] | MIPS.registers[Rt]); }

void OR(regAddr& Rd, regAddr& Rs, regAddr& Rt) { MIPS.registers[Rd] = MIPS.registers[Rs] | MIPS.registers[Rt]; }

void ORI(regAddr& Rd, regAddr& Rs, uint16_t const16){ MIPS.registers[Rd] = MIPS.registers[Rs] | const16; }

void WSBH(regAddr& Rd, regAddr& Rs)
{
    uint32_t oprnd = MIPS.registers[Rs];

    MIPS.registers[Rd] = 
        ((oprnd & 0xFF000000) >> 8) |
        ((oprnd & 0x00FF0000) << 8) |
        ((oprnd & 0x0000FF00) >> 8) |
        ((oprnd & 0x000000FF) << 8);

}

void XOR(regAddr& Rd, regAddr& Rs, regAddr& Rt) { MIPS.registers[Rd] = MIPS.registers[Rs] ^ MIPS.registers[Rt]; }

void XORI(regAddr& Rd, regAddr& Rs, uint16_t const16){ MIPS.registers[Rd] = MIPS.registers[Rs] ^ const16; }

void MOVN(regAddr& Rd, regAddr& Rs, regAddr& Rt) { if(MIPS.registers[Rt]) MIPS.registers[Rd] = MIPS.registers[Rs]; }

void MOVZ(regAddr& Rd, regAddr& Rs, regAddr& Rt) { if(not MIPS.registers[Rt]) MIPS.registers[Rd] = MIPS.registers[Rs]; }

void SLT(regAddr& Rd, regAddr& Rs, regAddr& Rt) // yet to add overflow trap
{
    int32_t a = static_cast<int32_t>(MIPS.registers[Rs]);
    int32_t b = static_cast<int32_t>(MIPS.registers[Rt]);

    MIPS.registers[Rd] = (a < b) ? 1 : 0;
}

void SLTI(regAddr& Rd, regAddr& Rs, uint16_t const16) // yet to add overflow trap
{
    int32_t a = static_cast<int32_t>(MIPS.registers[Rs]);
    int32_t b = static_cast<int16_t>(const16); // implicit casting will do sign extension after static cast

    MIPS.registers[Rd] = (a < b) ? 1 : 0;
}

void SLTIU(regAddr& Rd, regAddr& Rs, uint16_t const16) { MIPS.registers[Rd] = (MIPS.registers[Rs] < (int32_t(const16))) ? 1 : 0; }

void SLTU(regAddr& Rd, regAddr& Rs, regAddr& Rt) 
    { MIPS.registers[Rd] = (static_cast<int32_t>(MIPS.registers[Rs]) < static_cast<int32_t>(MIPS.registers[Rt])) ? 1 : 0; }

void ALIGN(regAddr& Rd, regAddr& Rs, regAddr& Rt, regAddr& bp) 
    { MIPS.registers[Rd] = (MIPS.registers[Rs] << (8*bp)) | (MIPS.registers[Rt] >> ((4 - bp) * 8)); }

void BITSWAP(regAddr& Rd, regAddr& Rt)
{
    uint32_t oprnd = MIPS.registers[Rt];
    uint32_t &ans = MIPS.registers[Rd];
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
    int64_t a = static_cast<int32_t>(MIPS.registers[Rs]);
    int64_t b = static_cast<int32_t>(MIPS.registers[Rt]);
    
    MIPS.registers[Rd] = ((a * b) & 0xFFFFFFFF);
}

void MUH(regAddr& Rd, regAddr& Rs, regAddr& Rt)
{
    int64_t a = static_cast<int32_t>(MIPS.registers[Rs]);
    int64_t b = static_cast<int32_t>(MIPS.registers[Rt]);

    MIPS.registers[Rd] = ((a * b) >> 32);
}

void MULU(regAddr& Rd, regAddr& Rs, regAddr& Rt)
    { MIPS.registers[Rd] = ((uint64_t(MIPS.registers[Rs]) * uint64_t(MIPS.registers[Rt])) & 0xFFFFFFFF); }

void MUHU(regAddr& Rd, regAddr& Rs, regAddr& Rt)
    { MIPS.registers[Rd] = ((uint64_t(MIPS.registers[Rs]) * uint64_t(MIPS.registers[Rt])) >> 32); }

// the program currently stops if value at Rt is zero and raises an exception. I need to change it so that it keeps executing.
// probably change the action to continue in the error specification there.

void DIV(regAddr& Rd, regAddr& Rs, regAddr& Rt)
    { MIPS.registers[Rd] = static_cast<int32_t>(MIPS.registers[Rs]) / static_cast<int32_t>(MIPS.registers[Rt]); }

void MOD(regAddr& Rd, regAddr& Rs, regAddr& Rt)
    { MIPS.registers[Rd] = static_cast<int32_t>(MIPS.registers[Rs]) % static_cast<int32_t>(MIPS.registers[Rt]); }

void DIVU(regAddr& Rd, regAddr& Rs, regAddr& Rt)
    { MIPS.registers[Rd] = MIPS.registers[Rs] / MIPS.registers[Rt]; }

void MODU(regAddr& Rd, regAddr& Rs, regAddr& Rt)
    { MIPS.registers[Rd] = MIPS.registers[Rs] % MIPS.registers[Rt]; }


// Address Computation and Large Constant

void LSA(regAddr& Rd, regAddr& Rs, regAddr& Rt, regAddr& sa)
    { MIPS.registers[Rd] = (MIPS.registers[Rs] << (sa + 1)) + MIPS.registers[Rt]; }

void AUI(regAddr& Rd, regAddr& Rs, uint16_t& immediate)
    { MIPS.registers[Rd] = int32_t(MIPS.registers[Rs]) + int32_t(uint32_t(immediate) << 16); }

// the below instructions are based on the hope that pc has moved on sequentially in each fetch after fetching this instruction
// if not, and some villian can make it jump before this instruction is completed, then you need to save the code.

void ADDIUPC(regAddr& Rd, uint32_t& immediate)
{
    uint32_t isNeg = immediate & 0x40000;
    MIPS.registers[Rd] = MIPS.PC - 8 + (((immediate & 0x3FFFF) << 2) | isNeg);
}

// its details in manual only says add to pc (i'm assuming that manual doesn't imply two different pc's between ADDIUPC
// and these two)
void ALUIPC(regAddr& Rd, uint16_t& immediate)
    {MIPS.registers[Rd] = (MIPS.PC - 8 + int32_t(uint32_t(immediate) << 16)) & 0xFFFF0000;}

void AUIPC(regAddr& Rd, uint16_t& immediate)
    {MIPS.registers[Rd] = MIPS.PC - 8 + int32_t(uint32_t(immediate) << 16);}

// two miscellaneous instructions (weirdly simple)
void SELNEZ(regAddr& Rd, regAddr& Rs, regAddr& Rt){ if(MIPS.registers[Rt]) MIPS.registers[Rd] = MIPS.registers[Rs]; }

void SELEQZ(regAddr& Rd, regAddr& Rs, regAddr& Rt){ if(not MIPS.registers[Rt]) MIPS.registers[Rd] = MIPS.registers[Rs]; }

// load and store instructions
void LB(regAddr& Rt, regAddr& base, uint16_t offset)
{
    MIPS.mem_channel.data = MIPS.registers[base] + int16_t(offset);
    MIPS.mem_channel.control = (0 << 5) | Rt;
    MIPS.mem_channel.addit = 0;
}

void LBU(regAddr& Rt, regAddr& base, uint16_t offset)
{
    MIPS.mem_channel.data = MIPS.registers[base] + int16_t(offset);
    MIPS.mem_channel.control = (0 << 5) | Rt;
    MIPS.mem_channel.addit = 1;
}

void LH(regAddr& Rt, regAddr& base, uint16_t offset)
{
    MIPS.mem_channel.data = MIPS.registers[base] + int16_t(offset);
    MIPS.mem_channel.control = (1 << 5) | Rt;
    MIPS.mem_channel.addit = 0;
}

void LHU(regAddr& Rt, regAddr& base, uint16_t offset)
{
    MIPS.mem_channel.data = MIPS.registers[base] + int16_t(offset);
    MIPS.mem_channel.control = (1 << 5) | Rt;
    MIPS.mem_channel.addit = 1;
}

void LW(regAddr& Rt, regAddr& base, uint16_t offset)
{
    MIPS.mem_channel.data = MIPS.registers[base] + int16_t(offset);
    MIPS.mem_channel.control = (3 << 5) | Rt;
    MIPS.mem_channel.addit = 0;
}

void SB(regAddr& Rt, regAddr& base, uint16_t offset)
{
    MIPS.mem_channel.data = MIPS.registers[base] + int16_t(offset);
    MIPS.mem_channel.control = (1 << 7) | (0 << 5) | Rt;
}

void SH(regAddr& Rt, regAddr& base, uint16_t offset)
{
    MIPS.mem_channel.data = MIPS.registers[base] + int16_t(offset);
    MIPS.mem_channel.control = (1 << 7) | (1 << 5) | Rt;
}

void SW(regAddr& Rt, regAddr& base, uint16_t offset)
{
    MIPS.mem_channel.data = MIPS.registers[base] + int16_t(offset);
    MIPS.mem_channel.control = (1 << 7) | (3 << 5) | Rt;
}