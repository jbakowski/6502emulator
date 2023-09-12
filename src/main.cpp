#include <iostream>
#include <stdint.h>
#include <6502.hpp>

int main() {
    CPU Cpu;
    Memory Mem;
    Clock Clock;
    Mem.Init();
    Cpu.Reset(Mem);
    std::cout << "Starting operations." << std::hex << std::endl; // just an excuse to turn on hex formatting
    // inline assembly
    Mem.Data[0x0000] = LDA_IMMEDIATE;
    Mem.Data[0x0001] = 0x33;
    Mem.Data[0x0002] = PHA_IMPLIED;
    Mem.Data[0x0003] = PLP_IMPLIED;
    Mem.Data[0x0004] = LDA_IMMEDIATE;
    Mem.Data[0x0005] = 0x43;
    Mem.Data[0x0006] = PHA_IMPLIED;
    Mem.Data[0x0007] = PHP_IMPLIED;
    Mem.Data[0x0008] = PLA_IMPLIED;
    Mem.Data[0x0009] = TAX_IMPLIED;
    Mem.Data[0x000A] = PLA_IMPLIED;
    Mem.Data[0x000B] = TAY_IMPLIED;
    // end inline assembly
    uint16_t programLength = 10;
    while(programLength > 0) {
        Cpu.InstructionCycle(Mem, Clock);
        programLength--;
    };
    std::cout << "Expected value of X register: 0" << std::endl;
    std::cout << "Expected value of Y register: 43" << std::endl;
    std::cout << "X register: " << (unsigned)Cpu.Register.IRX << std::endl;
    std::cout << "Y register: " << (unsigned)Cpu.Register.IRY << std::endl;
    std::cout << "Program exited succesfully" << std::endl;
}