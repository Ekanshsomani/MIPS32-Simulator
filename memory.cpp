#include <memory.hpp>

Memory::Memory(Processor& processor, Ram& segment)
    : proc(processor),
      ram(segment),
      addr(0),
      control(0),
      signExtend(0)
{

}

void Memory::call()
{
    bool write = (control >> 7) & 1;
    uint8_t width = ((control >> 5) & 0x03) + 1;
    uint32_t& reg = mips.registers[control & 0x1F];

    if(write)
    {
        for(int i=0; i<width; i++)
            ram.write(addr + i, 0xFFFF & (reg >> i));
    }
    else // if we are reading, then this
    {
        if(signExtend) // if sign_extend
        {
            switch(width)
            {
            case 1:
                reg = int8_t(ram.read(addr));
                break;
            
            default:
                reg = int16_t((ram.read(addr + 1) << 8) | ram.read(addr));
                break;
            }
        }
        else
        {
            for(int i=0; i<width; i++)
                reg |= ram.read(addr + i) << (8*i);
        }
    }

}
