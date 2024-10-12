#ifndef ELF_HPP
#define ELF_HPP

#include <ram.hpp>
#include <iostream>
#include <fstream>

class Elf
{
private:
    uint32_t e_entry; // 0x18
    uint32_t e_phoff; // 0x1C
    uint32_t e_shoff; // 0x20
    uint16_t e_ehsize; // 0x28
    uint16_t e_phnum; // 0x2C
    uint16_t e_shnum; // 0x30
    uint16_t e_shstrndx; // 0x32

    // Program header offsets relative to
    // program header start (at 0x34)
    uint32_t p_offset; // 0x04
    uint32_t p_vaddr; // 0x08
    uint32_t p_filesz; // 0x10
    uint32_t p_memsz; // 0x14
    // Include the below one if you want to do loading errors
    // uint32_t p_align; // 0x1C.


    // section header start (0x34 + 0x20)


    ifstream file;

    uint8_t readByte(const uint32_t& offset);

    uint16_t readHalf(const uint32_t& offset);

    uint32_t readWord(const uint32_t& offset);

public:
    Elf(string dir);

    Ram createSegment();
}

#endif