#include<funcs.hpp>

void fetch()
{
    uint32_t inst = RAM.read_word(MIPS.PC);
    uint8_t& control = MIPS.dec_channel.control;

    if(inst != 0)
    {
        uint8_t op = inst >> 26;

        switch (op)
        {
        case 0:
            op0(inst, control);
        break;
        
        default:
            break;
        }
    }
    
    MIPS.PC += 4;

    inst = 0;
    control = 0;
}

void op0(uint32_t inst, uint8_t& control)
{

}