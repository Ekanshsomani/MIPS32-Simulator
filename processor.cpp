#include <header.hpp>

using namespace std;


void Processor::bootUp()
{
    registers.resize(32);
    
    registers[0] = 0;
}

void Processor::hardCode()
{
    registers[0] = 0;
}