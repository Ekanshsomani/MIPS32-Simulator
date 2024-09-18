#include <header.hpp>

void fetch()
{
    uint32_t inst = RAM.read_word(MIPS.PC);
    
    MIPS.PC += 4;
}


