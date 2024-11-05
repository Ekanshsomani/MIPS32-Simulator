#include <main.hpp>

int main(int argc, char* argv[])
{
    elfile.loadData(ram);

    uint32_t prev{2};
    while(prev!=mips.PC)
    {
        prev = mips.PC;
        mips.cycle();
    }

    return 0;
}