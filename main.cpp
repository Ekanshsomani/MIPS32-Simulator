#include <funcs.hpp>

void memory()
{
    uint8_t& control = MIPS.mem_channel.control;
    bool write = (control >> 7) & 1;
    uint8_t width = ((control >> 5) & 0x03) + 1;
    
    uint32_t& reg = MIPS.registers[control & 0x1F];
    uint32_t& addr = MIPS.mem_channel.data;

    if(not write)
    {
        if(MIPS.mem_channel.addit) // if not sign_extend
        {
            for(int i=0; i<width; i++)
                reg |= RAM.read(addr + i) << (8*i);
        }
        else
        {
            switch(width)
            {
            case 1:
                reg = int8_t(RAM.read(addr));
                break;
            
            default:
                reg = int16_t((RAM.read(addr + 1) << 8) | RAM.read(addr));
                break;
            }
        }
    }
    else
    {
        for(int i=0; i<width; i++)
            RAM.write(addr + i, 0xFFFF & (reg >> i));
    }

    addr = 0;
    control = 0;
}