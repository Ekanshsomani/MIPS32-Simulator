#ifndef FUNCS_HPP
#define FUNCS_HPP

#include <unordered_map>
#include <vector>
#include <cstdint>
#include <functional>
#include <variant>

using namespace std;

typedef const uint8_t regAddr;

using FuncVariant = variant
<
    function(void(regAddr&, regAddr&)), // 000011
    function(void(regAddr&, regAddr&, regAddr&)), // 000111
    function(void(regAddr&, regAddr&, regAddr&, regAddr&)), // 001111
    function(void(regAddr&, regAddr&, const uint16_t&)), // 010011
    function(void(regAddr&, regAddr&, const uint32_t&)), // 100011
    function(void(regAddr&, const uint16_t&)), // 010001
    function(void(regAddr&, const uint32_t&)), // 100001
    function(void(uint32_t&)), // 100000
>

void ADD(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void ADDI(regAddr& Rd, regAddr& Rs, const uint16_t& const16);

void ADDIU(regAddr& Rd, regAddr& Rs, const uint16_t& const16);

void ADDU(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void CLO(regAddr& Rd, regAddr& Rs);

void CLZ(regAddr& Rd, regAddr& Rs);

void SEB(regAddr& Rd, regAddr& Rs);

void SEH(regAddr& Rd, regAddr& Rs);

void SUB(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void SUBU(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void ROTR(regAddr& Rd, regAddr& Rs, regAddr& bits5);

void ROTRV(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void SLL(regAddr& Rd, regAddr& Rs, regAddr& shift5);

void SLLV(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void SRA(regAddr& Rd, regAddr& Rs, regAddr& shift5);

void SRAV(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void SRL(regAddr& Rd, regAddr& Rs, regAddr& shift5);

void SRLV(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void AND(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void ANDI(regAddr& Rd, regAddr& Rs, const uint16_t& const16);

void EXT(regAddr& Rt, regAddr& Rs, regAddr& pos, regAddr& size);

void INS(regAddr& Rt, regAddr& Rs, regAddr& pos, regAddr& size);

void NOR(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void OR(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void ORI(regAddr& Rd, regAddr& Rs, const uint16_t& const16);

void WSBH(regAddr& Rd, regAddr& Rs);

void XOR(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void XORI(regAddr& Rd, regAddr& Rs, const uint16_t& const16);

void MOVN(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void MOVZ(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void SLT(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void SLTI(regAddr& Rd, regAddr& Rs, const uint16_t& const16);

void SLTIU(regAddr& Rd, regAddr& Rs, uint16_t& const16);

void SLTU(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void ALIGN(regAddr& Rd, regAddr& Rs, regAddr& Rt, regAddr& bp);

void BITSWAP(regAddr& Rd, regAddr& Rt);

void MUL(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void MUH(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void MULU(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void MUHU(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void DIV(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void MOD(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void DIVU(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void MODU(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void LSA(regAddr& Rd, regAddr& Rs, regAddr& Rt, regAddr& sa);

void AUI(regAddr& Rd, regAddr& Rs, const uint16_t& immediate);

void ADDIUPC(regAddr& Rd, const uint32_t& immediate);

void ALUIPC(regAddr& Rd, const uint16_t& immediate);

void AUIPC(regAddr& Rd, const uint16_t& immediate);

void SELNEZ(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void SELEQZ(regAddr& Rd, regAddr& Rs, regAddr& Rt);

void LB(regAddr& Rt, regAddr& base, const uint16_t& offset);

void LBU(regAddr& Rt, regAddr& base, const uint16_t& offset);

void LH(regAddr& Rt, regAddr& base, const uint16_t& offset);

void LHU(regAddr& Rt, regAddr& base, const uint16_t& offset);

void LW(regAddr& Rt, regAddr& base, const uint16_t& offset);

void SB(regAddr& Rt, regAddr& base, const uint16_t& offset);

void SH(regAddr& Rt, regAddr& base, const uint16_t& offset);

void SW(regAddr& Rt, regAddr& base, const uint16_t& offset);

void J(const uint32_t& instr_index);

void JAL(const uint32_t& instr_index);

void JALR(regAddr& Rd, regAddr& Rs);

void JALR_HB(regAddr& Rd, regAddr& Rs);

void BEQ(regAddr& Rs, regAddr& Rt, const uint16_t& offset);

void BNE(regAddr& Rs, regAddr& Rt, const uint16_t& offset);

void BGEZ(regAddr& Rs, const uint16_t& offset);

void BGTZ(regAddr& Rs, const uint16_t& offset);

void BLEZ(regAddr& Rs, const uint16_t& offset);

void BLTZ(regAddr& Rs, const uint16_t& offset);

void BC(const uint32_t& offset);

void BALC(const uint32_t& offset);

void JIC(regAddr& Rt, const uint16_t& offset);

void JIALC(regAddr& Rt, const uint16_t& offset);

void BEQC(regAddr& Rs, regAddr& Rt, const uint16_t& offset);

void BNEC(regAddr& Rs, regAddr& Rt, const uint16_t& offset);

void BLTC(regAddr& Rs, regAddr& Rt, const uint16_t& offset);

void BGEC(regAddr& Rs, regAddr& Rt, const uint16_t& offset);

void BLTUC(regAddr& Rs, regAddr& Rt, const uint16_t& offset);

void BGEUC(regAddr& Rs, regAddr& Rt, const uint16_t& offset);

void BEQZC(regAddr& Rs, const uint32_t& offset);

void BNEZC(regAddr& Rs, const uint32_t& offset);

void BEQZALC(regAddr& Rt, const uint16_t& offset);

void BNEZALC(regAddr& Rt, const uint16_t& offset);

void BLEZALC(regAddr& Rt, const uint16_t& offset);

void BGEZALC(regAddr& Rt, const uint16_t& offset);

void BGTZALC(regAddr& Rt, const uint16_t& offset);

void BLTZALC(regAddr& Rt, const uint16_t& offset);

void BOVC(regAddr& Rs, regAddr& Rt, const uint16_t& offset);

void BNVC(regAddr& Rs, regAddr& Rt, const uint16_t& offset);

#endif FUNCS_HPP