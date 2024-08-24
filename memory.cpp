#include <iostream>
#include <fstream>

#include <cstdint>

#include <vector>
#include <bitset>


using namespace std;

class Memory
{
    public:
        void loadMemory(const string& file_name)
        {
            ifstream file(file_name);
            if(not file)
            {
                cerr << "Error opening file: " << file_name << "\n";
                return;
            }

            string line;
            while(getline(file, line))
            {
                uint32_t temp = bitset<32>(line).to_ulong();
                instruction_memory.push_back(temp);
            }
            curr = 0;
            number_of_instructions = instruction_memory.size();
        }

        inline uint32_t fetch()
        {
            if(curr==number_of_instructions)
            {
                cerr << "End of Instructions!\n";
                return 0; // have to return something else 0 is a NOP instruction
            }
            return instruction_memory[curr++];
        }

    private:
        vector<uint32_t> instruction_memory;
        int curr, number_of_instructions;
};