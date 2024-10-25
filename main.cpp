#include <main.hpp>

int main(int argc, char* argv[])
{
    Elf elfile(argv[1]);
    Ram ram(elfile.reqRamSize());
    elfile.loadData(ram);

    Processor mips(ram);

    uint32_t prev{-1};
    while(prev!=mips.PC)
    {
        prev = mips.PC;
        mips.cycle();
    }

    return 0;
}