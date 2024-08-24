#include <header.hpp>

using namespace std;



void ADD(regAddr& Rd, regAddr& Rs, regAddr& Rt) // yet to add overflow trap
{
    int32_t a = static_cast<int32_t>(MIPS.registers[Rs]);
    int32_t b = static_cast<int32_t>(MIPS.registers[Rt]);
    int32_t c = a+b;

    MIPS.registers[Rd] = static_cast<uint32_t>(c);
}

void ADDI(regAddr& Rd, regAddr& Rs, uint16_t const16) // yet to add overflow trap
{
    int32_t a = static_cast<int32_t>(MIPS.registers[Rs]);
    int32_t b = static_cast<int16_t>(const16); // implicit casting will do sign extension after static cast
    int32_t c = a+b;

    MIPS.registers[Rd] = static_cast<uint32_t>(c);
}

void ADDIU(regAddr& Rd, regAddr& Rs, uint16_t const16) { MIPS.registers[Rd] = static_cast<uint32_t>(const16) + MIPS.registers[Rs]; }

void ADDU(regAddr& Rd, regAddr& Rs, uint32_t Rt) { MIPS.registers[Rd] = MIPS.registers[Rs] + MIPS.registers[Rt]; }

void CLO(regAddr& Rd, regAddr& Rs) { MIPS.registers[Rd] = __builtin_clz(~( MIPS.registers[Rs])); }

void CLZ(regAddr& Rd, regAddr& Rs) { MIPS.registers[Rd] = __builtin_clz(MIPS.registers[Rs]); }

void LUI(regAddr& Rd, uint16_t const16) { MIPS.registers[Rd] = static_cast<uint32_t>(const16)<<16; }

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
    int32_t a = static_cast<int32_t>(MIPS.registers[Rs]);
    int32_t b = static_cast<int32_t>(MIPS.registers[Rt]);
    int32_t c = a-b;

    MIPS.registers[Rd] = static_cast<uint32_t>(c);
}

void SUBU(regAddr& Rd, regAddr& Rs, regAddr& Rt) { MIPS.registers[Rd] = MIPS.registers[Rs] - MIPS.registers[Rt]; }

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




