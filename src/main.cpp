#include <iostream>
#include <stdint.h>
#include <6502.hpp>

int main() {
    CPU Cpu;
    Memory Mem;
    Clock Clock;
    Mem.Init();
    Cpu.Reset(Mem);
    uint8_t A = 0x30;
    uint8_t B = 0x40;
    std::cout << "Starting operations." << std::hex << std::endl; // just an excuse to turn on hex formatting
    // inline assembly
    Mem.Data[0x0000] = LDA_IMMEDIATE;
    Mem.Data[0x0001] = A;
    Mem.Data[0x0002] = JSR_ABSOLUTE;
    Mem.Data[0x0003] = 0x0040; // jmp to subroutine A
    Mem.Data[0x0004] = LDA_IMMEDIATE;
    Mem.Data[0x0005] = 0x50;
    // subroutine A
    Mem.Data[0x0040] = LDA_IMMEDIATE;
    Mem.Data[0x0041] = B;
    Mem.Data[0x0042] = LDX_ABSOLUTE;
    Mem.Data[0x0043] = 0x50;
    Mem.Data[0x0044] = RTS_IMPLIED;
    // end inline assembly
    uint16_t programLength = 10;
    while(programLength > 0) {
        Cpu.InstructionCycle(Mem, Clock);
        programLength--;
    };
    std::cout << "######" << std::endl;
    //std::cout << "Expected value of ACC register: " << A-B << std::endl;
    std::cout << "ACC: " << (unsigned)Cpu.Register.ACC << std::endl;
    std::cout << "IRX: " << (unsigned)Cpu.Register.IRX << std::endl;
    std::cout << "IRY: " << (unsigned)Cpu.Register.IRY << std::endl;
    std::cout << "Mem.Data[0x00FF]: " << (unsigned)Mem.Data[0x00FF] << std::endl;
    std::cout << "Program exited succesfully" << std::endl;
}