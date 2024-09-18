#include <header.hpp>

void fetch()
{
    uint32_t inst = RAM.read_word(MIPS.PC);
    MIPS.dec_channel[data] = inst
    MIPS.PC += 4;
}

void decode()
{
    uint32_t& inst = MIPS.dec_channel.data;
    uint8_t& control = MIPS.dec_channel.control;

    if(inst != 0)
    {
        uint8_t op = inst >> 26;
    }
    
    inst = 0;
    control = 0;
}

void memory()
{
    uint8_t& control = MIPS.mem_channel.control;
    bool write = (control >> 7) & 1;
    uint8_t width = (control >> 5) & 0x03;
    regAddr reg = control & 0x1F;
}