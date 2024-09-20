#include<funcs.hpp>

unordered_map<uint8_t, FuncVariant> opCall;

opCall[2] = J;
opCall[3] = JAL;
opCall[4] = BEQ;
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


void fetch()
{
    uint32_t inst{0};
    for(int i=0; i<4; i++)
                inst |= RAM.read(MIPS.PC + i) << (8*i);
    uint8_t& control = MIPS.dec_channel.control;

    if(inst != 0)
    {
        uint8_t op = inst >> 26;
    }
    
    MIPS.PC += 4;

    inst = 0;
    control = 0;
}

void op0(uint32_t inst, uint8_t& control)
{

}

void op1(uint32_t inst, uint8_t& control)
{

}

void op2(uint32_t inst, uint8_t& control)
{
    J(inst & 0x03FFFFFF);
}

void op3(uint32_t inst, uint8_t& control)
{
    
}

void op4(uint32_t inst, uint8_t& control)
{

}

void op5(uint32_t inst, uint8_t& control)
{
    
}

void op6(uint32_t inst, uint8_t& control)
{

}

void op7(uint32_t inst, uint8_t& control)
{
    
}

void op8(uint32_t inst, uint8_t& control)
{

}

void op9(uint32_t inst, uint8_t& control)
{
    
}

void op10(uint32_t inst, uint8_t& control)
{

}

void op11(uint32_t inst, uint8_t& control)
{
    
}

void op12(uint32_t inst, uint8_t& control)
{

}

void op13(uint32_t inst, uint8_t& control)
{
    
}

void op14(uint32_t inst, uint8_t& control)
{

}

void op15(uint32_t inst, uint8_t& control)
{
    
}

void op22(uint32_t inst, uint8_t& control)
{

}

void op23(uint32_t inst, uint8_t& control)
{
    
}

void op24(uint32_t inst, uint8_t& control)
{

}

void op28(uint32_t inst, uint8_t& control)
{
    
}

void op31(uint32_t inst, uint8_t& control)
{

}

void op50(uint32_t inst, uint8_t& control)
{
    
}

void op54(uint32_t inst, uint8_t& control)
{

}

void op58(uint32_t inst, uint8_t& control)
{

}

void op59(uint32_t inst, uint8_t& control)
{

}

void op62(uint32_t inst, uint8_t& control)
{
    
}