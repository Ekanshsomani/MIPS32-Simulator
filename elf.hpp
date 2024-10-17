#ifndef ELF_HPP
#define ELF_HPP

#include <ram.hpp>
#include <iostream>
#include <fstream>

class Elf
{
private:
    ifstream file;

    uint32_t e_entry; // 0x18
    uint32_t e_phoff; // 0x1C
    // uint32_t e_shoff; // 0x20
    // uint16_t e_ehsize; // 0x28 (probably not important)
    uint16_t e_phnum; // 0x2C
    // uint16_t e_shnum; // 0x30
    // uint16_t e_shstrndx; // 0x32

    // Program header offsets relative to
    // program header start (at 0x34)
    
    // uint32_t p_memsz; // 0x14
    // Include the below one if you want to do loading errors
    // uint32_t p_align; // 0x1C.


    // section header start (0x34 + 0x20*e_phnum)
    // uint32_t sh_name; // 0x00 (only offset is given here)
    // uint32_t sh_type; // 0x04
    // // uint32_t sh_flags; // 0x08 (useful if you want to distinguish
    // // between executable and non-executable memory)
    // uint32_t sh_addr; // 0x0C
    // uint32_t sh_offset; // 0x10
    // uint32_t sh_size; // 0x14

    uint8_t readByte(const uint32_t& offset);

    uint16_t readHalf(const uint32_t& offset);

    uint32_t readWord(const uint32_t& offset);

public:

    Elf(string dir);

    uint32_t reqRamSize();

    void loadData(Ram& ram);
}

#endif