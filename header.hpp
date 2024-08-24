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

    vector<uint32_t> registers;
    uint32_t HI, LO, cycle;

private:
    static const int sp = 29, gp = 28, ra = 31;
};

class Memory
{
public:
    void createMemory();
    
    void loadInstructions(const string& file_name);

    uint32_t getData(const uint32_t& addr);

private:
    vector<uint32_t> mem;
    uint32_t memory_size;
};

Processor MIPS;

