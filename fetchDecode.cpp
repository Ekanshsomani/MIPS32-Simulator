#include<funcs.hpp>
#include<unordered_set>

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

unordered_set<int> im_16_ops = {1, 6, 7};

// the three stages could be static objects with channels
// coming into them - feels right!

void fetch()
{
    uint32_t inst{0};
    for(int i=0; i<4; i++)
                inst |= RAM.read(MIPS.PC + i) << (8*i);
    uint8_t& control = MIPS.dec_channel.control;

    if(inst != 0)
    {
        uint8_t op = inst >> 26;

        if(im_16_ops.count(op)) im_16(inst, control);
        
    }
    
    MIPS.PC += 4;

    inst = 0;
    control = 0;
}

// im 21 is also being handled here for now
void im_16(const uin32_t& inst, const uint8_t& control)
{
    uint8_t op = inst >> 26;
    uint8_t rs = 0x1F & inst >> 21;
    uint8_t rt = 0x1F & inst >> 16;

    FuncVariant& func = MIPS.exec_channel.func;
    uint64_t& data = MIPS.exec_channel.data;
    uint8_t& control = MIPS.exec_channel.control;

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

void std_inst(const uint32_t& inst, const uint8_t& control)
{
    uint8_t op = inst >> 26;
    uint8_t rs = 0x1F & inst >> 21;
    uint8_t rt = 0x1F & inst >> 16;
    uint8_t rd = 0x1F & inst >> 11;
    uint8_t shamt = 0x1F & inst >> 6;
    uint8_t funct = 0x3F & inst;

    FuncVariant& func = MIPS.exec_channel.func;
    uint64_t& data = MIPS.exec_channel.data;
    uint8_t& control = MIPS.exec_channel.control;

    if(op == 31)
    {
        if(funct == 32)
        {
            if(shamt == 0) func = BITSWAP;
            else if((shamt >> 2) == 2)
            {
                func = ALIGN;
            }
        }
    }
}

