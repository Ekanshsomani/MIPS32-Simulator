#include <ram.hpp>

Ram::Ram(uint32_t size) : ramSize(size)
{ 
    vec.resize(size); 
}

bool Ram::checkBounds(const uint32_t& addr)
{
    if(addr < ramSize) return true;

    cerr << addr << " Read/Write address out of bounds :(\n";
    return false;
}

uint8_t Ram::read(const uint32_t& addr)
{
    if(checkBounds(addr)) return vec[addr]; 
    else return 0;
}

void Ram::write(const uint32_t& addr, uint8_t byte)
{
    if(checkBounds(addr)) vec[addr] = byte;
}