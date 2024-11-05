#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <vector>
#include <cstdint>

#include <decode.hpp>
#include <execute.hpp>
#include <memory.hpp>
#include <ram.hpp>

using namespace std;

class Processor
{
public:
    uint32_t registers[32];
    uint32_t HI, LO, PC;
    static const int sp = 29, gp = 28, ra = 31;

    Decode dec;
    Execute exec;
    Memory mem;

    Processor(Ram& ram);

    void cycle();
};

#endif