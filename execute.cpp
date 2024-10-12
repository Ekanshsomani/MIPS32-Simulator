#include <execute.hpp>

void Execute::execFunc(Args... args) 
{
    visit(& {
        using FuncType = decay_t<decltype(func)>;
        if constexpr (is_invocable_v<FuncType, Args...>) {
            func(args...);
        } else {
            cerr << "No matching function found for the given arguments.\n";
        }
    }, func);
}

void Execute::call()
{
    a1 = data & 0xFF;
    a2 = (data >> 8) & 0xFF;
    a3 = (data >> 16) & 0xFF;
    a4 = (data >> 24) & 0xFF;
    a5 = (data >> 32) & 0xFFFF;
    a6 = (data >> 32) & 0xFFFFFFFF;

    switch (control)
    {
    case 0b000011: execFunc(a1, a2); break;
    case 0b000111: execFunc(a1, a2, a3); break;
    case 0b001111: execFunc(a1, a2, a3, a4); break;
    case 0b010011: execFunc(a1, a2, a5); break;
    case 0b100011: execFunc(a1, a2, a6); break;
    case 0b010001: execFunc(a1, a5); break;
    case 0b100001: execFunc(a1, a6); break;
    case 0b100000: execFunc(a6); break;
    default: cerr << "Invalid control :(\n"; break;
    }
}