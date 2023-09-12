#include <6502.hpp>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <bitset>

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
    Register.SP  = 0xFF;    // stack grows downwards
    Status.C     = 0;
    Status.Z     = 0;
    Status.I     = 0;
    Status.D     = 0;
    Status.B     = 0;
    Status.O     = 0;
    Status.N     = 0;
};

uint8_t CPU::Fetch(Memory& Memory) {
    uint8_t retrievedData = Memory.Data[Register.PC];
    Register.PC++;
    return retrievedData;
}

void CPU::Store(Memory& Memory, uint8_t Data) {
    DEBUG_STDOUT("Register.PC: " << (unsigned)Register.PC << std::endl);
    DEBUG_STDOUT("Data to be saved: " << (unsigned)Data << std::endl);
    Memory.Data[Register.PC] = Data;
    DEBUG_STDOUT("Memory.Data[Register.PC]: " << (unsigned)Memory.Data[Register.PC] << std::endl);
    Register.PC++;
    DEBUG_STDOUT("Register.PC: " << (unsigned)Register.PC << std::endl);
}

void CPU::PushToStack(Memory& Memory, uint8_t Data) {
    DEBUG_STDOUT("Register.SP: " << (unsigned)Register.SP << std::endl);
    DEBUG_STDOUT("Data to be pushed: " << (unsigned)Data << std::endl);
    Memory.Data[Register.SP] = Data;
    DEBUG_STDOUT("Memory.Data[Register.SP]: " << (unsigned)Memory.Data[Register.SP] << std::endl);
    //assert(Register.SP < STACK_END && Register.SP > STACK_START);
    Register.SP--;
    DEBUG_STDOUT("Register.SP: " << (unsigned)Register.SP << std::endl);
}

uint8_t CPU::PopFromStack(Memory& Memory) {
    Register.SP++;
    DEBUG_STDOUT("Register.SP: " << (unsigned)Register.SP << std::endl);
    uint8_t poppedData = Memory.Data[Register.SP];
    DEBUG_STDOUT("Popped data: " << (unsigned)poppedData << std::endl);
    //assert(Register.SP < STACK_END && Register.SP > STACK_START);
    return poppedData;
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
    uint8_t opcode = Fetch(Memory); // fetch stage
    DEBUG_STDOUT ("Opcode read: " << (unsigned)opcode << std::endl); 
    switch(opcode) {                // decode stage
        case LDA_IMMEDIATE:         // execute stage
            DEBUG_STDOUT ("Accumulator (before): " << (unsigned)Register.ACC << std::endl);
            Register.ACC = Fetch(Memory);
            DEBUG_STDOUT("Accumulator (after): " << (unsigned)Register.ACC << std::endl);
            SetZeroFlag(Status, Register.ACC);
            SetNegativeFlag(Status, Register.ACC);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            DEBUG_STDOUT("Status flags (C-Z-I-D-B-O-N) [LDA]: " << (unsigned)Status.C << (unsigned)Status.Z << (unsigned)Status.I << (unsigned)Status.D << (unsigned)Status.B << (unsigned)Status.O << (unsigned)Status.N << std::endl);
            Clock.Tick(LDA_IMMEDIATE_CYCLE);
            break;
        case LDX_IMMEDIATE:
            DEBUG_STDOUT("Register X (before): " << (unsigned)Register.IRX << std::endl);
            Register.IRX = Fetch(Memory);
            DEBUG_STDOUT("Register X (after): " << (unsigned)Register.IRX << std::endl);
            SetZeroFlag(Status, Register.IRX);
            SetNegativeFlag(Status, Register.IRX);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(LDX_IMMEDIATE_CYCLE);
            break;
        case LDY_IMMEDIATE:
            DEBUG_STDOUT("Register Y (before): " << (unsigned)Register.IRY << std::endl);
            Register.IRY = Fetch(Memory);
            DEBUG_STDOUT("Register Y (after): " << (unsigned)Register.IRY << std::endl);
            SetZeroFlag(Status, Register.IRY);
            SetNegativeFlag(Status, Register.IRY);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(LDY_IMMEDIATE_CYCLE);
            break;
        case STA_ZERO_PAGE:
            Store(Memory, Register.ACC);
            Clock.Tick(STA_ZERO_PAGE_CYCLE);
            break;
        case STX_ZERO_PAGE:
            Store(Memory, Register.IRX);
            Clock.Tick(STX_ZERO_PAGE_CYCLE);
            break;
        case STY_ZERO_PAGE:
            Store(Memory, Register.IRY);
            Clock.Tick(STY_ZERO_PAGE_CYCLE);
            break;
        case TAX_IMPLIED:
            DEBUG_STDOUT("Register.IRX (before): " << (unsigned)Register.IRX << std::endl);
            DEBUG_STDOUT("Register.ACC (before): " << (unsigned)Register.ACC << std::endl);
            Register.IRX = Register.ACC;
            DEBUG_STDOUT("Register.IRX (after): " << (unsigned)Register.IRX << std::endl);
            SetZeroFlag(Status, Register.IRX);
            DEBUG_STDOUT("Status.Z: " << (unsigned)Status.Z << std::endl);
            SetNegativeFlag(Status, Register.IRX);
            DEBUG_STDOUT("Status.N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(TAX_IMPLIED_CYCLE);
            break;
        case TAY_IMPLIED:
            DEBUG_STDOUT("Register.IRY (before): " << (unsigned)Register.IRY << std::endl);
            DEBUG_STDOUT("Register.ACC (before): " << (unsigned)Register.ACC << std::endl);
            Register.IRY = Register.ACC;
            DEBUG_STDOUT("Register.IRY (after): " << (unsigned)Register.IRY << std::endl);
            SetZeroFlag(Status, Register.IRY);
            DEBUG_STDOUT("Status.Z: " << (unsigned)Status.Z << std::endl);
            SetNegativeFlag(Status, Register.IRY);
            DEBUG_STDOUT("Status.N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(TAY_IMPLIED_CYCLE);
        case TXA_IMPLIED:
            DEBUG_STDOUT("Register.ACC (before): " << (unsigned)Register.ACC << std::endl);
            DEBUG_STDOUT("Register.IRX (before): " << (unsigned)Register.IRX << std::endl);
            Register.ACC = Register.IRX;
            DEBUG_STDOUT("Register.ACC (after): " << (unsigned)Register.ACC << std::endl);
            SetZeroFlag(Status, Register.ACC);
            SetNegativeFlag(Status, Register.ACC);
            Clock.Tick(TXA_IMPLIED_CYCLE);
            break;
        case TYA_IMPLIED:
            DEBUG_STDOUT("Register.ACC (before): " << (unsigned)Register.ACC << std::endl);
            DEBUG_STDOUT("Register.IRY (before): " << (unsigned)Register.IRY << std::endl);
            Register.ACC = Register.IRY;
            DEBUG_STDOUT("Register.ACC (after): " << (unsigned)Register.ACC << std::endl);
            SetZeroFlag(Status, Register.ACC);
            DEBUG_STDOUT("Status.Z: " << (unsigned)Status.Z << std::endl);
            SetNegativeFlag(Status, Register.ACC);
            DEBUG_STDOUT("Status.N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(TYA_IMPLIED_CYCLE);
            break;
        case TSX_IMPLIED:
            DEBUG_STDOUT("Register.IRX (before): " << (unsigned)Register.IRX << std::endl);
            DEBUG_STDOUT("Register.SP (before): " << (unsigned)Register.SP << std::endl);
            Register.IRX = Register.SP;
            DEBUG_STDOUT("Register.SP (after): " << (unsigned)Register.SP << std::endl);
            SetZeroFlag(Status, Register.IRX);
            DEBUG_STDOUT("Status.Z: " << (unsigned)Status.Z << std::endl);
            SetNegativeFlag(Status, Register.IRX);
            DEBUG_STDOUT("Status.N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(TSX_IMPLIED_CYCLE);
            break;
        case TXS_IMPLIED:
            DEBUG_STDOUT("Register.SP (before): " << (unsigned)Register.SP << std::endl);
            DEBUG_STDOUT("Register.IRX (before): " << (unsigned)Register.IRX << std::endl);
            Register.SP = Register.IRX;
            DEBUG_STDOUT("Register.SP (after): " << (unsigned)Register.SP << std::endl);
            Clock.Tick(TXS_IMPLIED_CYCLE);
            break;
        case PHA_IMPLIED:
            DEBUG_STDOUT("Accumulator: " << (unsigned)Register.ACC << std::endl);
            PushToStack(Memory, Register.ACC);
            DEBUG_STDOUT("Status flags (C-Z-I-D-B-O-N) [PHA]: " << (unsigned)Status.C << (unsigned)Status.Z << (unsigned)Status.I << (unsigned)Status.D << (unsigned)Status.B << (unsigned)Status.O << (unsigned)Status.N << std::endl);
            Clock.Tick(PHA_IMPLIED_CYCLE);
            break;
        case PHP_IMPLIED:
        {   
            // TODO: there must be a nicer way to do this
            DEBUG_STDOUT("Status flags (C-Z-I-D-B-O-N) [actual]: " << (unsigned)Status.C << (unsigned)Status.Z << (unsigned)Status.I << (unsigned)Status.D << (unsigned)Status.B << (unsigned)Status.O << (unsigned)Status.N << std::endl);
            uint8_t statusCopy = 0;
            statusCopy = statusCopy || (0b01000000 & Status.C) || (0b00100000 & Status.Z) || (0b00010000 & Status.I) || (0b00001000 & Status.D) || (0b00000100 & Status.B) || (0b00000010 & Status.O) || (0b00000001 & Status.N);
            DEBUG_STDOUT("Status flags [read into a single var]: " << (unsigned)statusCopy << std::endl);
            PushToStack(Memory, statusCopy);
            Clock.Tick(PHP_IMPLIED_CYCLE);
            break;
        }
        case PLA_IMPLIED:
            DEBUG_STDOUT("Accumulator (before): " << (unsigned)Register.ACC << std::endl);
            Register.ACC = PopFromStack(Memory);
            SetZeroFlag(Status, Register.ACC);
            SetNegativeFlag(Status, Register.ACC);
            DEBUG_STDOUT("Accumulator (after): " << (unsigned)Register.ACC << std::endl);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(PLA_IMPLIED_CYCLE);
            break;
        case PLP_IMPLIED:
        {
            // TODO: there must be a nicer way to do this
            DEBUG_STDOUT("Status flags (C-Z-I-D-B-O-N) [before]: " << (unsigned)Status.C << (unsigned)Status.Z << (unsigned)Status.I << (unsigned)Status.D << (unsigned)Status.B << (unsigned)Status.O << (unsigned)Status.N << std::endl);
            uint8_t statusCopy = PopFromStack(Memory);
            DEBUG_STDOUT("Data popped from stack: " << (unsigned)statusCopy << std::endl);
            DEBUG_STDOUT("Data popped from stack: " << std::bitset<8>(statusCopy) << std::endl);
            Status.C = (statusCopy >> 6) & 0x01;
            Status.Z = (statusCopy >> 5) & 0x01;
            Status.I = (statusCopy >> 4) & 0x01;
            Status.D = (statusCopy >> 3) & 0x01;
            Status.B = (statusCopy >> 2) & 0x01;
            Status.O = (statusCopy >> 1) & 0x01;
            Status.N = (statusCopy) & 0x01;
            DEBUG_STDOUT("Status flags (C-Z-I-D-B-O-N) [after]: " << (unsigned)Status.C << (unsigned)Status.Z << (unsigned)Status.I << (unsigned)Status.D << (unsigned)Status.B << (unsigned)Status.O << (unsigned)Status.N << std::endl);
            Clock.Tick(PLP_IMPLIED_CYCLE);
            break;
        }
        default:
            break;
    }
}