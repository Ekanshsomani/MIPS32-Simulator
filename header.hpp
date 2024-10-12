#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>
#include <functional>
#include <variant>

using namespace std;

typedef const uint8_t regAddr;

using FuncVariant = variant
<
    function(void(regAddr, regAddr)), // 000011
    function(void(regAddr, regAddr, regAddr)), // 000111
    function(void(regAddr, regAddr, regAddr, regAddr)), // 001111
    function(void(regAddr, regAddr, uint16_t)), // 010011
    function(void(regAddr, regAddr, uint32_t)), // 100011
    function(void(regAddr, uint16_t)), // 010001
    function(void(regAddr, uint32_t)), // 100001
    function(void(uint32_t)), // 100000
>

struct Channels
{
    uint32_t data;
    uint8_t control;
    bool addit;
};

struct exChannel
{
    FuncVariant func;
    uint8_t control;
    uint64_t data;
};

class Processor
{
public:
    void bootUp();

    void hardCode(); // run this command after each cycle

    vector<uint32_t> registers;
    uint32_t HI, LO, cycle, PC;
    static const int sp = 29, gp = 28, ra = 31;
    Channels dec_channel, mem_channel;
    exChannel exec_channel;
};

class Memory
{
public:
	void create_memory(uint32_t mem_size);
	uint8_t read(const uint32_t& addr);
    void write(const uint32_t& addr, uint8_t byte);

private:
	vector<uint8_t> mem;
};

Processor mips;
Processor cp0; // use inheritance and give cp0 an inherited class if they need something specific that mips can't have
Memory ram;

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

