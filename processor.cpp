#include <processor.hpp>

Processor::Processor(Ram& ram)
    : dec(*this),
      exec(*this),
      mem(*this, ram),
      PC(0)
{
    registers[0] = 0;
}

void Processor::cycle()
{
    mem.call();
    exec.call();
    dec.call();
    registers[0] = 0;
}