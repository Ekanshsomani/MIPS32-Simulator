#include <elf.hpp>

Elf::Elf(string dir) 
: file(dir, ios::binary),
  e_entry(readWord(0x18)),
  e_phoff(readWord(0x1C)),
  e_phnum(readHalf(0x2C))
{
    
}

uint32_t Elf::reqRamSize()
{
    uint32_t ans = 0;
    for(int i=0; i < e_phnum; i++)
        ans += readWord(e_phoff + i * 0x20 + 0x14);

    if(ans > 40_000_000) 
        cerr << "Memory required for file is too high";
    
    return ans;
}

void Elf::loadData(Ram& ram)
{
    uint32_t p_offset; // 0x04
    uint32_t p_vaddr; // 0x08
    uint32_t p_filesz; // 0x10
    for(int i = 0; i < e_phnum; i++)
    {
        p_offset = readWord(e_phoff + i * 0x20 + 0x04);
        p_vaddr = readWord(e_phoff + i * 0x20 + 0x08);
        p_filesz = readWord(e_phoff + i * 0x20 + 0x10);

        for(uint32_t j = 0; j < p_filesz; j++)
            ram.write(p_vaddr + j, readByte(p_offset + j));
    }
}

uint8_t Elf::readByte(const uint32_t& offset)
{
    file.seekg(offset, ios::beg);
    uint8_t ans;
    file.read(reinterpret_cast<char*>(ans), sizeof(uint8_t));
    return *ans;
}

uint16_t Elf::readHalf(const uint32_t& offset)
{
    uint16_t ans = readByte(offset) | (readByte(offset + 1) << 8);
    return ans;
}

uint32_t Elf::readWord(const uint32_t& offset)
{
    uint32_t ans{0};
    for(int i=0; i<4; i++) ans |= (readByte(offset + i) << (i << 3));
    return ans;
}