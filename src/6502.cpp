#include <6502.hpp>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

//
//  MEMORY
//

void Memory::Init() {
    for(uint32_t i = 0; i < MEM_MAX; i++) {
        Data[i] = 0;
    }
}

//
//  CLOCK
//

void Clock::SetClockFrequency(uint32_t freq) {
    ClockFrequency   = freq;
    ClockPeriod      = 1/freq;    // recalculate clock period
}

void Clock::Tick(uint32_t ticks) {
    #ifdef _WIN32
        Sleep(ticks*ClockPeriod*1000);
    #else
        usleep(ticks*ClockPeriod*1000000);
    #endif
}

//
//  CPU
//

void CPU::Reset(Memory& Memory) {
    // read address from POWER_ON_RESET
    // jump to the address
    // activate the routine
    Register.ACC = 0;
    Register.IRX = 0;
    Register.IRY = 0;
    Register.PC  = 0;
    Register.SP  = 0;
    StatusFlag.C = 0;
    StatusFlag.Z = 0;
    StatusFlag.D = 0;
    StatusFlag.B = 0;
    StatusFlag.O = 0;
    StatusFlag.N = 0;
};

uint8_t CPU::Fetch(Memory& Memory, Clock& Clock) {
    uint8_t retrievedData = Memory.Data[Register.PC];
    Register.PC++;
    Clock.Tick(FETCH_BYTE_CYCLE);
    return retrievedData;
}

void CPU::InstructionCycle(Memory& Memory, Clock& Clock) {
    uint8_t x;
    uint8_t opcode = Fetch(Memory, Clock); // fetch stage
    std::cout << "Opcode read: " << (unsigned)opcode << std::endl; 
    switch(opcode) {                       // decode stage
        case LDA_IMMEDIATE:                // execute stage
            std::cout << "Accumulator: " << (unsigned)Register.ACC << std::endl;
            Register.ACC = Fetch(Memory, Clock);
            std::cout << "Accumulator: " << (unsigned)Register.ACC << std::endl;
            if(Register.ACC == 0x00) {
                StatusFlag.Z = 1;
            } else {
                StatusFlag.Z = 0;
            }
            if(Register.ACC & 0b10000000) {
                StatusFlag.N = 1;
            } else {
                StatusFlag.N = 0;
            }
            std::cout << "Status flag Z: " << (unsigned)StatusFlag.Z << std::endl;
            std::cout << "Status flag N: " << (unsigned)StatusFlag.N << std::endl;
            break;
        default:
            break;
    }
}