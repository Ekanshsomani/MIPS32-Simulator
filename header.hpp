#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>

using namespace std;

typedef const uint8_t regAddr;


class Processor
{
public:
    void bootUp();

    void hardCode(); // run this command after each cycle

    vector<uint32_t> registers;
    uint32_t HI, LO, cycle, PC;
    static const int sp = 29, gp = 28, ra = 31;
};

class Memory
{
public:
	void createMemory(uint32_t mem_size);
	void loadInstructions(const uint32_t& start_addr, const uint32_t& end_addr);
	uint32_t get_Data(const uint32_t& addr);
private:
	vector<uint8_t> mem;
    uint32_t memory_size;
};

Processor MIPS;
Processor cp0; // use inheritance and give cp0 inherited classes if they need something specific that MIPS can't have
Memory RAM;

// IO will either end up being an instance object of the parent memory class
// that imports all the input from a file onto a pariticular section on the memory
// and takes input from there. It writes output onto memory, that we export into
// another file at the end.
Memory IO; 
// OR there will be a separate program, that's constantly running in parallel with
// the simulator, that takes input from keyboard and immediately loads it onto a section 
// of memory that our simulator can read. And there is another section of memory where
// our simulator can write the output, and the program will be constantly reading that
// memory and displaying that output on the screen.