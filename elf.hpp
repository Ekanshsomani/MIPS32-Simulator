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
    uint16_t e_phnum; // 0x2C

    uint8_t readByte(const uint32_t& offset);

    uint16_t readHalf(const uint32_t& offset);

    uint32_t readWord(const uint32_t& offset);

public:

    Elf(string dir);

    uint32_t reqRamSize();

    void loadData(Ram& ram);
};

#endif