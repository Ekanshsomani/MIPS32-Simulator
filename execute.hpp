#ifndef EXECUTE_HPP
#define EXECUTE_HPP

#include <funcs.hpp>
#include <processor.hpp>

template <typename... Args> 

class Execute
{
private:
    regAddr a1, a2, a3, a4;
    uint16_t a5;
    uint32_t a6;

    Processor& processor;

public:
    FuncVariant func;
    uint8_t control;
    uint64_t data;

    Execute(Processor& proc);

    void call();

    void execFunc(Args... args);
};

#endif