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
    // TODO
    // read address from POWER_ON_RESET
    // jump to the address
    // activate the routine
    Register.ACC = 0;
    Register.IRX = 0;
    Register.IRY = 0;
    Register.PC  = 0;
    Register.SP  = 0;
    Status.C     = 0;
    Status.Z     = 0;
    Status.D     = 0;
    Status.B     = 0;
    Status.O     = 0;
    Status.N     = 0;
};

uint8_t CPU::Fetch(Memory& Memory, Clock& Clock) {
    uint8_t retrievedData = Memory.Data[Register.PC];
    Register.PC++;
    Clock.Tick(FETCH_BYTE_CYCLE);
    return retrievedData;
}

void CPU::Store(Memory& Memory, Clock& Clock, uint8_t Data) {
    Memory.Data[Register.PC] = Data;
    Register.PC++;
    Clock.Tick(FETCH_BYTE_CYCLE);
}

void CPU::SetZeroFlag(StatusFlag& StatusFlag, uint16_t Register) {
    if (Register == 0) {
        StatusFlag.Z = 1;
    } else {
        StatusFlag.Z = 0;
    }
}

void CPU::SetNegativeFlag(StatusFlag& StatusFlag, uint16_t Register) {
    if (Register & 0b10000000) {
        StatusFlag.N = 1;
    } else {
        StatusFlag.N = 0;
    }
}

void CPU::InstructionCycle(Memory& Memory, Clock& Clock) {
    uint8_t x;
    uint8_t opcode = Fetch(Memory, Clock); // fetch stage
    DEBUG_STDOUT ("Opcode read: " << (unsigned)opcode << std::endl); 
    switch(opcode) {                       // decode stage
        case LDA_IMMEDIATE:                // execute stage
            DEBUG_STDOUT ("Accumulator: " << (unsigned)Register.ACC << std::endl);
            Register.ACC = Fetch(Memory, Clock);
            DEBUG_STDOUT("Accumulator: " << (unsigned)Register.ACC << std::endl);
            SetZeroFlag(Status, Register.ACC);
            SetNegativeFlag(Status, Register.ACC);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            break;
        case LDX_IMMEDIATE:
            DEBUG_STDOUT("Register X: " << (unsigned)Register.IRX << std::endl);
            Register.IRX = Fetch(Memory, Clock);
            DEBUG_STDOUT("Register X: " << (unsigned)Register.IRX << std::endl);
            SetZeroFlag(Status, Register.IRX);
            SetNegativeFlag(Status, Register.IRX);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            break;
        case LDY_IMMEDIATE:
            DEBUG_STDOUT("Register Y: " << (unsigned)Register.IRY << std::endl);
            Register.IRY = Fetch(Memory, Clock);
            DEBUG_STDOUT("Register Y: " << (unsigned)Register.IRY << std::endl);
            SetZeroFlag(Status, Register.IRY);
            SetNegativeFlag(Status, Register.IRY);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            break;
        case STA_ZERO_PAGE:
            Store(Memory, Clock, Register.ACC);
            Clock.Tick(1);
            break;
        case STX_ZERO_PAGE:
            Store(Memory, Clock, Register.IRX);
            Clock.Tick(1);
            break;
        case STY_ZERO_PAGE:
            Store(Memory, Clock, Register.IRY);
            Clock.Tick(1);
            break;
        case TAX_IMPLIED:
            Register.IRX = Register.ACC;
            SetZeroFlag(Status, Register.IRX);
            SetNegativeFlag(Status, Register.IRX);
            Clock.Tick(2);
        case TAY_IMPLIED:
            Register.IRY = Register.ACC;
            SetZeroFlag(Status, Register.IRY);
            SetNegativeFlag(Status, Register.IRY);
            Clock.Tick(2);
        case TXA_IMPLIED:
            Register.ACC = Register.IRX;
            SetZeroFlag(Status, Register.ACC);
            SetNegativeFlag(Status, Register.ACC);
            Clock.Tick(2);
        case TYA_IMPLIED:
            Register.ACC = Register.IRY;
            SetZeroFlag(Status, Register.ACC);
            SetNegativeFlag(Status, Register.ACC);
            Clock.Tick(2);
        case TSX_IMPLIED:
            Register.IRX = Register.SP;

        default:
            break;
    }
}