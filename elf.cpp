#include <elf.hpp>

Elf::Elf(string dir) : file(dir, ios::binary)
{
    
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

Ram Elf::createSegment()
{
    
}