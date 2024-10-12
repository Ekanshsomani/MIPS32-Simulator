#ifndef DECODE_HPP
#define DECODE_HPP

#include<processor.hpp>
#include <execute.hpp>
#include<funcs.hpp>

#include<unordered_set>

using namespace std;

class Decode
{
private:
    uint32_t inst;
    uint8_t op;
    uint8_t rs;
    uint8_t rt;
    uint8_t rd;
    uint8_t shamt;
    uint8_t funct;
    uint16_t im16;
    uint32_t imlarge; // either 19, 21, 23 or 26 bit?
    
    uint64_t &exData;
    uint8_t &exControl;
    FuncVariant &exFunc;

    Processor& proc;

public:
    uint8_t control;

    Decode(Processor& processor)

    void fetch();

    void call();

    void itype();
}

#endif DECODE_HPP