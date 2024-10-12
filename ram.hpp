#ifndef RAM_HPP
#define RAM_HPP

#include <vector>
#include <cstdint>

using namespace std;

class Ram
{
private:
    vector<uint8_t> vec;
    int ramSize;

    bool checkBounds(const uint32_t& addr);

public:
    Ram(uint32_t size);
    uint8_t read(const uint32_t& addr);
    void write(const uint32_t& addr, uint8_t byte);

}

#endif