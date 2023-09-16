#include <iostream>
#include <stdint.h>
#include <6502.hpp>

int main() {
    CPU Cpu;
    Memory Mem;
    Clock Clock;
    Mem.Init();
    Cpu.Reset(Mem);
    uint8_t A = 0b11001111;
    uint8_t B = 0b10001001;
    std::cout << "Starting operations." << std::hex << std::endl; // just an excuse to turn on hex formatting
    // inline assembly
    Mem.Data[0x00FF] = B;
    Mem.Data[0x0000] = LDA_IMMEDIATE;
    Mem.Data[0x0001] = A;
    Mem.Data[0x0002] = BIT_TEST_ZEROPAGE;
    Mem.Data[0x0003] = 0x0FF;
    // end inline assembly
    uint16_t programLength = 2;
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