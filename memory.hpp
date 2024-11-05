#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <processor.hpp>

class Memory
{
private:
    Processor& proc;
    Ram& ram;

public:
    uint32_t addr;
    uint8_t control;
    bool signExtend;

    Memory(Processor& processor, Ram& segment);

    void call();
};

#endif