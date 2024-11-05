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

    void zeroOps();

    void normieOps();

    void otherOps();

    void oneType(regAddr& a1, regAddr& a2);

    void twoType(regAddr& a1, regAddr& a2, regAddr& a3);

    void threeType(regAddr& a1, regAddr& a2, regAddr& a3, regAddr& a4);

    void fourType(regAddr& a1, regAddr& a2, const uint16_t& a3);

    void fiveType(regAddr& a1, regAddr& a2, const uint32_t& a3);

    void sixType(regAddr& a1, const uint16_t& a2);

    void sevenType(regAddr& a1, const uint32_t& a2);

    void eightType(const uint32_t& a1);

public:
    uint8_t control;

    Decode(Processor& processor)

    void fetch();

    void call();
};

#endif