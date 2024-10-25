#ifndef MAIN_HPP
#define MAIN_HPP

#include <processor.hpp>
#include <ram.hpp>
#include <elf.hpp>

using namespace std;

// Basic Main:
// Load an ELF file
// Create a Ram on the basis of ELF file specifications
// create a Processor
// start the instruction execution! (BOOM!)

// Final Target Main: (for now)
// Load an ELF file
// Create a RAM on the basis of ELF file specifications
// Create a Processor Object (main MIPS32 Processor)
// Create a CP0 Processor Object (Interfaces with OS)
// Create an OS object
// Repeat the following:
    // Continue the intruction processing
    // If Syscall, process CP0 Object
        // If CP0 Object signals something to OS object
        // OS Object would take care of that (IO and other such stuff!)
    // continue once CP0 resolves Syscall
        // I can't be more specific right now! :-|




#endif