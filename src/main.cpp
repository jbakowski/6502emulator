#include <iostream>
#include <stdint.h>
#include <6502.hpp>

int main() {
    CPU Cpu;
    Memory Mem;
    Clock Clock;
    Mem.Init();
    Cpu.Reset(Mem);
    // inline assembly
    Mem.Data[0x0000] = LDA_IMMEDIATE;
    Mem.Data[0x0001] = 0xFF;
    Mem.Data[0x0002] = LDX_IMMEDIATE;
    Mem.Data[0x0003] = 0x00;
    Mem.Data[0x0004] = LDY_IMMEDIATE;
    Mem.Data[0x0005] = 0xAA;
    // end inline assembly
    uint16_t programLength = 6;
    while(programLength > 0) {
        Cpu.InstructionCycle(Mem, Clock);
        programLength--;
    };

    std::cout << "Program exited succesfully" << std::endl;
}