#include <decode.hpp>

const unordered_map<uint8_t, FuncVariant> opCall = {
    {2, J},
    {3, JAL},
    {4, BEQ},
    {5, BNE},
    {9, ADDIU},
    {10, SLTI},
    {11, SLTIU},
    {12, ANDI},
    {13, ORI},
    {14, XORI},
    {15, AUI},
    {22, BGEC},
    {23, BLTC},
    {50, BC},
    {58, BALC}
}; // index based on op code


const unordered_map<uint8_t, FuncVariant> op0 = {
    {0, SLL},
    {3, SRA},
    {4, SLLV},
    {5, LSA},
    {7, SRAV},
    {16, CLZ},
    {17, CLO},
    {32, ADD},
    {33, ADDU},
    {34, SUB},
    {35, SUBU},
    {36, AND},
    {37, OR},
    {38, XOR},
    {39, NOR},
    {42, SLT},
    {43, SLTU}
}; // index based on func if op code is 0

Decode::Decode(Processor& Processor)
:
  proc = Processor,
  exData = proc.exec.data,
  exControl = proc.exec.control,
  exFunc = proc.exec.func
{

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

    static const unordered_set<int> othOps = {1, 6, 7, 8, 24, 31, 54, 59, 62};

    if(inst != 0)
    {

        if(op == 0) zeroOps();
        else if(opCall.count(op)) normieOps();
        else if(othOps.count(op)) otherOps();
        else cerr << "We need to do more work on decode :(";
    }

    mips.PC += 4;
}

void Decode::zeroOps()
{
    twoType(rd, rs, rt);
    if(op0.count(funct)) exFunc = op0[funct];
    else if(funct == 2)
    {
        if(rs) exFunc = ROTR;
        else exFunc = SRL;
    }
    else if(funct == 6)
    {
        if(shamt) exFunc = ROTRV;
        else exFunc = SRLV;
    }
    else if(funct == 9)
    {
        oneType(rd, rs);

        if(shamt >> 4) exFunc = JALR_HB;
        else exFunc = JALR;
    }
    else if(funct > 47 and funct < 52)
    {
        const vector<vector<FuncVariant>> vec = {
            {MUL, MUH},
            {MULU, MUHU},
            {DIV, MOD},
            {DIVU, MODU}
        };

        exFunc = vec[funct - 48][shamt - 2];
    }
    else
    {
        cerr << "You need a better instruction when op = 0 :(";
    }
}

void Decode::normieOps()
{
    exFunc = opCall[op];
    fourType(rs, rt, im16);

    static const unordered_set<int> im26 = {2, 3, 50, 58};
    if(im26.count(op)) eightType(inst & 0x03FFFFFF);
}

void Decode::otherOps()
{
    fourType(rs, rt, im16);
    if(op == 1)
    {
        sixType(rs, im16);
        if(rt == 0) func = BLTZ;
        else if(rt == 1) func = BGEZ;
    }
    else if(op == 6)
    {
        sixType(rt, im16);
        if(rt == 0) { func = BLEZ; sixType(rs, im16); }
        else if(rs == 0) func = BLEZALC;
        else if(rs == rt) func = BGEZALC;
        else { func = BGEUC; fourType(rs, rt, im16); }
    }
    else if(op == 7)
    {
        sixType(rt, im16);
        if(rt == 0) { func = BGTZ; sixType(rs, im16); }
        else if(rs == 0) func = BGTZALC;
        else if(rs == rt) func = BLTZALC;
        else { func = BLTUC; fourType(rs, rt, im16);}
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
    else if(op == 31)
    {
        if(shamt == 0) {exFunc = BITSWAP; oneType(rd, rt);}
        else if((shamt >> 2) == 2)
        {
            exFunc = ALIGN;
            threeType(rd, rs, rt, shamt & 0b11);
        }
    }
    else if(op == 54)
    {
        if(rs == 0) { func = JIC; sixType(rt, im16); }
        else { func = BEQZC; sevenType(rs, inst & 0x1FFFFF); }
    }
    else if(op == 59)
    {
        if(rt & 0x18)
        {
            sixType(rs, im16);
            if(rt & 1) func = ALUIPC;
            else func = AUIPC;
        }
        else
        {
            sevenType(rs, inst & 0x7FFFF);
            func = ADDIUPC;
        }
    }
    else if(op == 62)
    {
        if(rs == 0)
        {
            sixType(rt, im16);
            func = JIALC;
        }
        else
        {
            sixType(rs, im16);
            func = BNEZC;
        }
    }
}

void Decode::oneType(regAddr& a1, regAddr& a2)
{
    exControl = 0b000011;
    exData = (a2 << 8) | a2;
}

void Decode::twoType(regAddr& a1, regAddr& a2, regAddr& a3)
{
    exControl = 0b000111;
    exData = (a3 << 16) | (a2 << 8) | a1;
}

void Decode::threeType(regAddr& a1, regAddr& a2, regAddr& a3, regAddr& a4)
{
    exControl = 0b001111;
    exData = (a4 << 24) | (a3 << 16) | (a2 << 8) | a1;
}

void Decode::fourType(regAddr& a1, regAddr& a2, const uint16_t& a3)
{
    exControl = 0b010011;
    exData = (a3 << 32) | (a2 << 8) | a1;
}

void Decode::fiveType(regAddr& a1, regAddr& a2, const uint32_t& a3)
{
    exControl = 0b100011;
    exData = (a3 << 32) | (a2 << 8) | a1;
}

void Decode::sixType(regAddr& a1, const uint16_t& a2)
{
    exControl = 0b010001;
    exData = (a2 << 32) | a1;
}

void Decode::sevenType(regAddr& a1, const uint32_t& a2)
{
    exControl = 0b100001;
    exData = (a2 << 32) | a1;
}

void Decode::eightType(const uint32_t& a1)
{
    exControl = 0b1000000;
    exData = a1 << 32;
}