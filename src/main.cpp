#include <iostream>
#include <stdint.h>
#include <6502.hpp>

int main() {
    CPU Cpu;
    Memory Mem;
    Clock Clock;
    Mem.Init();
    Cpu.Reset(Mem);
    uint8_t LastVal = 0x50;
    uint8_t desiredFibonacci = 7; // accepted values: 1 - 7
    std::cout << "Starting operations." << std::hex << std::endl; // just an excuse to turn on hex formatting
    // inline assembly
    Mem.Data[0x0000] = LDY_IMMEDIATE;
    Mem.Data[0x0001] = desiredFibonacci - 1; // Nth fibonacci number
    Mem.Data[0x0002] = LDA_IMMEDIATE;
    Mem.Data[0x0003] = 0x00;
    Mem.Data[0x0004] = STA_ZEROPAGE;
    Mem.Data[0x0005] = LastVal;
    Mem.Data[0x0006] = LDA_IMMEDIATE;
    Mem.Data[0x0007] = 0x01;
    // loop start
    Mem.Data[0x0008] = TAX_IMPLIED;
    Mem.Data[0x0009] = CLC_IMPLIED;
    Mem.Data[0x000A] = ADC_ZEROPAGE;
    Mem.Data[0x000B] = LastVal;
    Mem.Data[0x000C] = STX_ZEROPAGE;
    Mem.Data[0x000D] = LastVal;
    Mem.Data[0x000E] = DEY_IMPLIED;
    Mem.Data[0x000F] = BNE_RELATIVE;
    Mem.Data[0x0010] = -9;
    // loop end
    // end inline assembly
    uint16_t programLength = 4 + 6*desiredFibonacci;
    while(programLength > 0) {
        Cpu.InstructionCycle(Mem, Clock);
        programLength--;
    };
    std::cout << "######" << std::endl;
    Cpu.PrintCpuStatus();
}