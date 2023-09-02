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
    Mem.Data[0x0000] = 0xA9;
    Mem.Data[0x0001] = 0xFF;
    Mem.Data[0x0002] = 0xA9;
    Mem.Data[0x0003] = 0x00;
    // end inline assembly
    Cpu.InstructionCycle(Mem, Clock);
    Cpu.InstructionCycle(Mem, Clock);

    std::cout << "Program exited succesfully" << std::endl;
}