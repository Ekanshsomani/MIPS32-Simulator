#include <decode.hpp>

unordered_map<uint8_t, FuncVariant> opCall; // index based on op code
unordered_map<uint8_t, FuncVariant> op0; // index based on func if op code is 0

opCall[2] = J;
opCall[3] = JAL;
opCall[4] = BEQ;
opCall[5] = BNE;
opCall[9] = ADDIU;
opCall[10] = SLTI;
opCall[11] = SLTIU;
opCall[12] = ANDI;
opCall[13] = ORI;
opCall[14] = XORI;
opCall[15] = AUI;
opCall[22] = BGEC;
opCall[23] = BLTC;
opCall[50] = BC;
opCall[58] = BALC;

op0[0] = SLL;
op0[3] = SRA;
op0[4] = SLLV;
op0[5] = LSA;
op0[7] = SRAV;
op0[16] = CLZ;
op0[17] = CLO;
op0[32] = ADD;
op0[33] = ADDU;
op0[34] = SUB;
op0[35] = SUBU;
op0[36] = AND;
op0[37] = OR;
op0[38] = XOR;
op0[39] = NOR;
op0[42] = SLT;
op0[43] = SLTU;

const unordered_set<int> im_ops = {1, 6, 7, 8, 24, 54, 59, 62};

Deocde::Decode(Processor& Processor):
{
    proc = Processor;
    exData = proc.exec.data;
    exControl = proc.exec.control;
    exFunc = proc.exec.func;
}

void Decode::fetch()
{
    inst = 0;
    for(int i=0; i<4; i++)
        inst |= ram.read(mips.PC + i) << (8*i);

    op = inst >> 26;
    rs = 0x1F & inst >> 21;
    rt = 0x1F & inst >> 16;
    rd = 0x1F & inst >> 11;
    shamt = 0x1F & inst >> 6;
    funct = 0x3F & inst;
    im16 = 0xFFFF & inst;
}

void Decode::call()
{
    fetch();

    if(inst != 0)
    {
        if(im_ops.count(op)) itype();

        if(op == 31)
        {
            if(funct == 32)
            {
                if(shamt == 0) exFunc = BITSWAP;
                else if((shamt >> 2) == 2)
                {
                    exFunc = ALIGN;
                }
            }
        }
    }

    mips.PC += 4;
}

void Decode::itype()
{
    if(op == 1)
    {
        if(rt == 0) func = BLTZ;
        else if(rt == 1) func = BGEZ;
    }
    else if(op == 6)
    {
        if(rt == 0) func = BLEZ;
        else if(rs == 0) func = BLEZALC;
        else if(rs == rt) func = BGEZALC;
        else func = BGEUC;
    }
    else if(op == 7)
    {
        if(rt == 0) func = BGTZ;
        else if(rs == 0) func = BGTZALC;
        else if(rs == rt) func = BLTZALC;
        else func = BLTUC;
    }
    else if(op == 8)
    {
        if(rs < rt) func = BEQC;
        else func = BOVC;
    }
    else if(op == 24)
    {
        if(rs < rt) func = BNEC;
        else func = BNVC;
    }
    else if(op == 54)
    {
        if(rs == 0)
        {
            func = JIC;
        }
        else
        {
            func = BEQZC;
        }
    }
    else if(op == 59)
    {
        if(rt & 0x18)
        {
            if(rt & 1) func = ALUIPC;
            else func = AUIPC;
        }
        else
        {
            func = ADDIUPC;
        }
    }
    else if(op == 62)
    {
        if(rs == 0)
        {
            func = JIALC;
        }
        else
        {
            func = BNEZC;
        }
    }
}