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
    Memory.Data[Register.PC] = Data;
    Register.PC++;
}

uint8_t CPU::ReadByte(Memory& Memory, uint16_t Address) {
    return Memory.Data[Address];
};

void CPU::WriteByte(Memory& Memory, uint16_t Address, uint8_t Data) {
    Memory.Data[Address] = Data;
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

void CPU::PrintCpuStatus() {
    std::cout << "### Registers" << std::endl;
    std::cout << "# ACC: " << (unsigned)Register.ACC << std::endl;
    std::cout << "# IRX: " << (unsigned)Register.IRX << std::endl;
    std::cout << "# IRY: " << (unsigned)Register.IRY << std::endl;
    std::cout << "# PC:  " << (unsigned)Register.PC  << std::endl;
    std::cout << "# SP:  " << (unsigned)Register.SP  << std::endl;
    std::cout << "### Status flags" << std::endl;
    std::cout << "# Carry:             " << (unsigned)Status.C << std::endl;
    std::cout << "# Zero:              " << (unsigned)Status.Z << std::endl;
    std::cout << "# Interrupt disable: " << (unsigned)Status.I << std::endl;
    std::cout << "# Decimal mode:      " << (unsigned)Status.D << std::endl;
    std::cout << "# Break:             " << (unsigned)Status.B << std::endl;
    std::cout << "# Overflow:          " << (unsigned)Status.O << std::endl;
    std::cout << "# Negative:          " << (unsigned)Status.N << std::endl;
 }

void CPU::InstructionCycle(Memory& Memory, Clock& Clock) {
    uint8_t opcode = Fetch(Memory); // fetch stage
    switch(opcode) {                // decode stage
        case LDA_IMMEDIATE:         // execute stage
            DEBUG_STDOUT("---------- " << "LDA_IMMEDIATE" << " ----------" << std::endl);
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
            DEBUG_STDOUT("---------- " << "LDX_IMMEDIATE" << " ----------" << std::endl);
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
            DEBUG_STDOUT("---------- " << "LDY_IMMEDIATE" << " ----------" << std::endl);
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
            DEBUG_STDOUT("---------- " << "STA_ZERO_PAGE" << " ----------" << std::endl);
            Store(Memory, Register.ACC);
            Clock.Tick(STA_ZERO_PAGE_CYCLE);
            break;
        case STX_ZERO_PAGE:
            DEBUG_STDOUT("---------- " << "STX_ZERO_PAGE" << " ----------" << std::endl);
            Store(Memory, Register.IRX);
            Clock.Tick(STX_ZERO_PAGE_CYCLE);
            break;
        case STY_ZERO_PAGE:
            DEBUG_STDOUT("---------- " << "STY_ZERO_PAGE" << " ----------" << std::endl);
            Store(Memory, Register.IRY);
            Clock.Tick(STY_ZERO_PAGE_CYCLE);
            break;
        case TAX_IMPLIED:
            DEBUG_STDOUT("---------- " << "TAX_IMPLIED" << " ----------" << std::endl);
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
            DEBUG_STDOUT("---------- " << "TAY_IMPLIED" << " ----------" << std::endl);
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
            DEBUG_STDOUT("---------- " << "TXA_IMPLIED" << " ----------" << std::endl);
            DEBUG_STDOUT("Register.ACC (before): " << (unsigned)Register.ACC << std::endl);
            DEBUG_STDOUT("Register.IRX (before): " << (unsigned)Register.IRX << std::endl);
            Register.ACC = Register.IRX;
            DEBUG_STDOUT("Register.ACC (after): " << (unsigned)Register.ACC << std::endl);
            SetZeroFlag(Status, Register.ACC);
            SetNegativeFlag(Status, Register.ACC);
            Clock.Tick(TXA_IMPLIED_CYCLE);
            break;
        case TYA_IMPLIED:
            DEBUG_STDOUT("---------- " << "TYA_IMPLIED" << " ----------" << std::endl);
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
            DEBUG_STDOUT("---------- " << "TSX_IMPLIED" << " ----------" << std::endl);
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
            DEBUG_STDOUT("---------- " << "TXS_IMPLIED" << " ----------" << std::endl);
            DEBUG_STDOUT("Register.SP (before): " << (unsigned)Register.SP << std::endl);
            DEBUG_STDOUT("Register.IRX (before): " << (unsigned)Register.IRX << std::endl);
            Register.SP = Register.IRX;
            DEBUG_STDOUT("Register.SP (after): " << (unsigned)Register.SP << std::endl);
            Clock.Tick(TXS_IMPLIED_CYCLE);
            break;
        case PHA_IMPLIED:
            DEBUG_STDOUT("---------- " << "PHA_IMPLIED" << " ----------" << std::endl);
            DEBUG_STDOUT("Accumulator: " << (unsigned)Register.ACC << std::endl);
            PushToStack(Memory, Register.ACC);
            DEBUG_STDOUT("Status flags (C-Z-I-D-B-O-N) [PHA]: " << (unsigned)Status.C << (unsigned)Status.Z << (unsigned)Status.I << (unsigned)Status.D << (unsigned)Status.B << (unsigned)Status.O << (unsigned)Status.N << std::endl);
            Clock.Tick(PHA_IMPLIED_CYCLE);
            break;
        case PHP_IMPLIED:
        {   
            DEBUG_STDOUT("---------- " << "PHP_IMPLIED" << " ----------" << std::endl);
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
            DEBUG_STDOUT("---------- " << "PLA_IMPLIED" << " ----------" << std::endl);
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
            DEBUG_STDOUT("---------- " << "PLP_IMPLIED" << " ----------" << std::endl);
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
        case AND_IMMEDIATE:
        {
            DEBUG_STDOUT("---------- " << "AND_IMMEDIATE" << " ----------" << std::endl);
            DEBUG_STDOUT("Accumulator status [before]: " << (unsigned)Register.ACC << std::endl);
            uint8_t data = Fetch(Memory);
            DEBUG_STDOUT("Data fetched: " << (unsigned)data << std::endl);
            Register.ACC = Register.ACC & data;
            SetZeroFlag(Status, Register.ACC);
            SetNegativeFlag(Status, Register.ACC);
            DEBUG_STDOUT("Accumulator status [after]: " << (unsigned)Register.ACC << std::endl);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(AND_IMMEDIATE_CYCLE);
            break;
        }
        case EOR_IMMEDIATE:
        {
            DEBUG_STDOUT("---------- " << "EOR_IMMEDIATE" << " ----------" << std::endl);
            DEBUG_STDOUT("Accumulator status [before]: " << (unsigned)Register.ACC << std::endl);
            uint8_t data = Fetch(Memory);
            DEBUG_STDOUT("Data fetched: " << (unsigned)data << std::endl);
            Register.ACC = Register.ACC ^ data;
            SetZeroFlag(Status, Register.ACC);
            SetNegativeFlag(Status, Register.ACC);
            DEBUG_STDOUT("Accumulator status [after]: " << (unsigned)Register.ACC << std::endl);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(EOR_IMMEDIATE_CYCLE);
            break;
        }
        case ORA_IMMEDIATE:
        {
            DEBUG_STDOUT("---------- " << "ORA_IMPLIED" << " ----------" << std::endl);
            DEBUG_STDOUT("Accumulator status [before]: " << (unsigned)Register.ACC << std::endl);
            uint8_t data = Fetch(Memory);
            DEBUG_STDOUT("Data fetched: " << (unsigned)data << std::endl);
            Register.ACC = Register.ACC | data;
            SetZeroFlag(Status, Register.ACC);
            SetNegativeFlag(Status, Register.ACC);
            DEBUG_STDOUT("Accumulator status [after]: " << (unsigned)Register.ACC << std::endl);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(ORA_IMMEDIATE_CYCLE);
            break;
        }
        case BIT_TEST_ZEROPAGE:
        {
            DEBUG_STDOUT("---------- " << "BIT_TEST_ZEROPAGE" << " ----------" << std::endl);
            DEBUG_STDOUT("Accumulator status [before]: " << (unsigned)Register.ACC << std::endl);
            uint8_t dataAddress = Fetch(Memory);
            DEBUG_STDOUT("Data address: " << (unsigned)dataAddress << std::endl);
            uint8_t data = ReadByte(Memory, dataAddress);
            uint8_t mask = 0;
            DEBUG_STDOUT("Data fetched: " << (unsigned)data << std::endl);
            mask = Register.ACC & data;
            DEBUG_STDOUT("Mask: " << (unsigned)mask << std::endl);
            if (mask == 0) {
                Status.Z = 1;
            }
            Status.O = (mask >> 6) & 0x1;
            Status.N = (mask >> 7) & 0x1;
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag O: " << (unsigned)Status.O << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(BIT_TEST_ZEROPAGE_CYCLE);
            break;
        }
        case ADC_IMMEDIATE:
        {
            DEBUG_STDOUT("---------- " << "ADC_IMMEDIATE" << " ----------" << std::endl);
            DEBUG_STDOUT("Accumulator status [before]: " << (unsigned)Register.ACC << std::endl);
            DEBUG_STDOUT("Carry flag: " << (unsigned)Status.C << std::endl);
            uint8_t data = Fetch(Memory);

            uint8_t differentSign = 0;
            uint8_t operandXor = 0;

            // if bit 7 of operandXor is 1 - the signs of ACC and data are different
            operandXor = Register.ACC ^ data;
            if ((operandXor >> 7) & Status.N) {
                differentSign = 1;
            }
            DEBUG_STDOUT("Different sign of the values: " << (unsigned)differentSign<< std::endl);
            
            uint16_t sum = Register.ACC;

            sum = sum + data;
            sum = sum + Status.C;

            Register.ACC = sum & 0xFF;
            if(sum > 0xFF) {
                Status.C = 1;
            }
            SetZeroFlag(Status, Register.ACC);
            SetNegativeFlag(Status, Register.ACC);

            operandXor = Register.ACC ^ data;
            // oldDifferentSign != newDifferentSign -> overflow
            if(differentSign != ((operandXor >> 7) & Status.N)) {
                Status.O = 1;
            }
            DEBUG_STDOUT("Status flag C: " << (unsigned)Status.C << std::endl);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag O: " << (unsigned)Status.O << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(ADC_IMMEDIATE_CYCLE);
            break;
        }
        case SBC_IMMEDIATE:
        {
            DEBUG_STDOUT("---------- " << "SBC_IMMEDIATE" << " ----------" << std::endl);
            DEBUG_STDOUT("Accumulator status [before]: " << (unsigned)Register.ACC << std::endl);
            DEBUG_STDOUT("Carry flag: " << (unsigned)Status.C << std::endl);
            uint8_t data = Fetch(Memory);

            uint8_t differentSign = 0;
            uint8_t operandXor = 0;

            // if bit 7 of operandXor is 1 - the signs of ACC and data are different
            operandXor = Register.ACC ^ data;
            if ((operandXor >> 7) & Status.N) {
                differentSign = 1;
            }
            DEBUG_STDOUT("Different sign of the values: " << (unsigned)differentSign<< std::endl);
            
            int16_t sum = Register.ACC;

            sum = sum - data;
            sum = sum - Status.C;

            Register.ACC = sum & 0xFF;
            if(sum > 0xFF) {
                Status.C = 0;
            }
            SetZeroFlag(Status, Register.ACC);
            SetNegativeFlag(Status, Register.ACC);

            operandXor = Register.ACC ^ data;
            // oldDifferentSign != newDifferentSign -> overflow
            if(differentSign != ((operandXor >> 7) & Status.N)) {
                Status.O = 1;
            }
            DEBUG_STDOUT("Status flag C: " << (unsigned)Status.C << std::endl);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag O: " << (unsigned)Status.O << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(SBC_IMMEDIATE_CYCLE);
            break;
        }
        case CMP_IMMEDIATE:
        {
            DEBUG_STDOUT("---------- " << "CMP_IMMEDIATE" << " ----------" << std::endl);
            uint8_t data = Fetch(Memory);
            DEBUG_STDOUT("Accumulator status: " << (unsigned)Register.ACC << std::endl);
            DEBUG_STDOUT("Data: " << (unsigned)data << std::endl);
            if(data == Register.ACC) {
                Status.Z = 1;
            }
            if(Register.ACC > data) {
                Status.C = 1;
            }
            if(data > Register.ACC) {
                Status.N = 1;
            }
            DEBUG_STDOUT("Status flag C: " << (unsigned)Status.C << std::endl);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(CMP_IMMEDIATE_CYCLE);
            break;
        }
        case CPX_IMMEDIATE:
        {
            DEBUG_STDOUT("---------- " << "CPX_IMMEDIATE" << " ----------" << std::endl);
            uint8_t data = Fetch(Memory);
            DEBUG_STDOUT("IRX status: " << (unsigned)Register.IRX << std::endl);
            DEBUG_STDOUT("Data: " << (unsigned)data << std::endl);
            if(data == Register.IRX) {
                Status.Z = 1;
            }
            if(Register.IRX > data) {
                Status.C = 1;
            }
            if(data > Register.IRX) {
                Status.N = 1;
            }
            DEBUG_STDOUT("Status flag C: " << (unsigned)Status.C << std::endl);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(CPX_IMMEDIATE_CYCLE);
            break;
        }
        case CPY_IMMEDIATE:
        {
            DEBUG_STDOUT("---------- " << "CPY_IMMEDIATE" << " ----------" << std::endl);
            uint8_t data = Fetch(Memory);
            DEBUG_STDOUT("IRY status: " << (unsigned)Register.IRY << std::endl);
            DEBUG_STDOUT("Data: " << (unsigned)data << std::endl);
            if(data == Register.IRY) {
                Status.Z = 1;
            }
            if(Register.IRY > data) {
                Status.C = 1;
            }
            if(data > Register.IRY) {
                Status.N = 1;
            }
            DEBUG_STDOUT("Status flag C: " << (unsigned)Status.C << std::endl);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(CPY_IMMEDIATE_CYCLE);
            break;
        }
        case INC_ZEROPAGE:
        {   
            DEBUG_STDOUT("---------- " << "INC_ZEROPAGE" << " ----------" << std::endl);
            uint8_t dataAddress = Fetch(Memory);
            DEBUG_STDOUT("Data address: " << (unsigned)dataAddress << std::endl);
            uint8_t data = ReadByte(Memory, dataAddress);
            DEBUG_STDOUT("Data [before]: " << (unsigned)data << std::endl);
            data = data + 1;
            DEBUG_STDOUT("Data [after]: " << (unsigned)data << std::endl);
            SetNegativeFlag(Status, data);
            SetZeroFlag(Status, data);
            WriteByte(Memory, dataAddress, ReadByte(Memory, dataAddress) + 1);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(INC_ZEROPAGE_CYCLE);
            break;
        }
        case INX_IMPLIED:
            DEBUG_STDOUT("---------- " << "INX_ZEROPAGE" << " ----------" << std::endl);
            DEBUG_STDOUT("IRX [before]: " << (unsigned)Register.IRX << std::endl);
            Register.IRX = Register.IRX + 1;
            DEBUG_STDOUT("IRX [after]: " << (unsigned)Register.IRX << std::endl);
            SetNegativeFlag(Status, Register.IRX);
            SetZeroFlag(Status, Register.IRX);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(INX_IMPLIED_CYCLE);
            break;
        case INY_IMPLIED:
            DEBUG_STDOUT("---------- " << "INY_ZEROPAGE" << " ----------" << std::endl);
            DEBUG_STDOUT("IRY [before]: " << (unsigned)Register.IRY << std::endl);
            Register.IRY = Register.IRY + 1;
            DEBUG_STDOUT("IRY [after]: " << (unsigned)Register.IRY << std::endl);
            SetNegativeFlag(Status, Register.IRY);
            SetZeroFlag(Status, Register.IRY);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(INY_IMPLIED_CYCLE);
            break;
        case DEC_ZEROPAGE:
        {
            DEBUG_STDOUT("---------- " << "DEC_ZEROPAGE" << " ----------" << std::endl);
            uint8_t dataAddress = Fetch(Memory);
            DEBUG_STDOUT("Data address: " << (unsigned)dataAddress << std::endl);
            uint8_t data = ReadByte(Memory, dataAddress);
            DEBUG_STDOUT("Data [before]: " << (unsigned)data << std::endl);
            data = data - 1;
            DEBUG_STDOUT("Data [after]: " << (unsigned)data << std::endl);
            SetNegativeFlag(Status, data);
            SetZeroFlag(Status, data);
            WriteByte(Memory, dataAddress, ReadByte(Memory, dataAddress) - 1);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(DEC_ZEROPAGE_CYCLE);
            break;
        }
        case DEX_IMPLIED:
            DEBUG_STDOUT("---------- " << "DEX_ZEROPAGE" << " ----------" << std::endl);
            DEBUG_STDOUT("IRX [before]: " << (unsigned)Register.IRX << std::endl);
            Register.IRX = Register.IRX - 1;
            DEBUG_STDOUT("IRX [before]: " << (unsigned)Register.IRX << std::endl);
            SetNegativeFlag(Status, Register.IRX);
            SetZeroFlag(Status, Register.IRX);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(DEX_IMPLIED_CYCLE);
            break;
        case DEY_IMPLIED:
            DEBUG_STDOUT("---------- " << "DEY_ZEROPAGE" << " ----------" << std::endl);
            DEBUG_STDOUT("IRY [before]: " << (unsigned)Register.IRY << std::endl);
            Register.IRY = Register.IRY - 1;
            DEBUG_STDOUT("IRY [before]: " << (unsigned)Register.IRY << std::endl);
            SetNegativeFlag(Status, Register.IRY);
            SetZeroFlag(Status, Register.IRY);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(DEY_IMPLIED_CYCLE);
            break;
        case ASL_ACCUMULATOR:
            DEBUG_STDOUT("---------- " << "ASL_ACCUMULATOR" << " ----------" << std::endl);
            DEBUG_STDOUT("ACC [before]: " << (unsigned)Register.ACC << std::endl);
            Status.C = ((Register.ACC >> 7) & 0x1);
            Register.ACC = (Register.ACC << 1);
            DEBUG_STDOUT("ACC [after]: " << (unsigned)Register.ACC << std::endl);
            Status.N = (Register.ACC << 7);
            if(Register.ACC == 0) {
                Status.Z = 1;
            };
            DEBUG_STDOUT("Status flag C: " << (unsigned)Status.C << std::endl);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(ASL_ACCUMULATOR_CYCLE);
            break;
        case LSR_ACCUMULATOR:
        {
            DEBUG_STDOUT("---------- " << "LSR_ACCUMULATOR" << " ----------" << std::endl);
            DEBUG_STDOUT("ACC [before]: " << (unsigned)Register.ACC << std::endl);
            Status.C = ((Register.ACC << 7) & 0x1);
            Register.ACC = (Register.ACC >> 1);
            DEBUG_STDOUT("ACC [after]: " << (unsigned)Register.ACC << std::endl);
            Status.N = (Register.ACC >> 7);
            if(Register.ACC == 0) {
                Status.Z = 1;
            };
            DEBUG_STDOUT("Status flag C: " << (unsigned)Status.C << std::endl);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(LSR_ACCUMULATOR_CYCLE);
            break;
        }
        case ROL_ACCUMULATOR:
        {
            DEBUG_STDOUT("---------- " << "ROL_ACCUMULATOR" << " ----------" << std::endl);
            DEBUG_STDOUT("ACC [before]: " << (unsigned)Register.ACC << std::endl);
            uint8_t temp = (Register.ACC << 1);
            temp = temp | (0x1 & Status.C);
            Status.C = ((Register.ACC >> 7) & 0x1);
            Register.ACC = temp;
            DEBUG_STDOUT("ACC [after]: " << (unsigned)Register.ACC << std::endl);
            Status.N = (Register.ACC >> 7);
            if(Register.ACC == 0) {
                Status.Z = 1;
            };
            DEBUG_STDOUT("Status flag C: " << (unsigned)Status.C << std::endl);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(ROL_ACCUMULATOR_CYCLE);
            break;
        }
        case ROR_ACCUMULATOR:
        {
            DEBUG_STDOUT("---------- " << "ROR_ACCUMULATOR" << " ----------" << std::endl);
            DEBUG_STDOUT("ACC [before]: " << (unsigned)Register.ACC << std::endl);
            uint8_t temp = (Register.ACC >> 1);
            temp = temp | (Status.C << 7);
            Status.C = (Register.ACC & 0x1);
            Register.ACC = temp;
            DEBUG_STDOUT("ACC [after]: " << (unsigned)Register.ACC << std::endl);
            Status.N = (Register.ACC >> 7);
            if(Register.ACC == 0) {
                Status.Z = 1;
            };
            DEBUG_STDOUT("Status flag C: " << (unsigned)Status.C << std::endl);
            DEBUG_STDOUT("Status flag Z: " << (unsigned)Status.Z << std::endl);
            DEBUG_STDOUT("Status flag N: " << (unsigned)Status.N << std::endl);
            Clock.Tick(ROR_ACCUMULATOR_CYCLE);
            break;
        }
        case JMP_ABSOLUTE:
        {
            DEBUG_STDOUT("---------- " << "JMP_ABSOLUTE" << " ----------" << std::endl);
            uint8_t jmpAddress = Fetch(Memory);
            DEBUG_STDOUT("PC [before]: " << (unsigned)Register.PC << std::endl);
            DEBUG_STDOUT("Jump to address: " << (unsigned)jmpAddress << std::endl);
            Register.PC = jmpAddress;
            DEBUG_STDOUT("PC [after]: " << (unsigned)Register.PC << std::endl);
            Clock.Tick(JMP_ABSOLUTE_CYCLE);
            break;
        }
        case JSR_ABSOLUTE:
        {
            DEBUG_STDOUT("---------- " << "JSR_ABSOLUTE" << " ----------" << std::endl);
            uint8_t jmpAddress = Fetch(Memory);
            DEBUG_STDOUT("PC [before]: " << (unsigned)Register.PC << std::endl);
            DEBUG_STDOUT("Jump to address: " << (unsigned)jmpAddress << std::endl);
            PushToStack(Memory, Register.PC);
            Register.PC = jmpAddress;
            DEBUG_STDOUT("PC [after]: " << (unsigned)Register.PC << std::endl);
            Clock.Tick(JSR_ABSOLUTE_CYCLE);
            break;
        }
        case RTS_IMPLIED:
            DEBUG_STDOUT("---------- " << "RTS_IMPLIED" << " ----------" << std::endl);
            DEBUG_STDOUT("PC [before]: " << (unsigned)Register.PC << std::endl);
            Register.PC = PopFromStack(Memory);
            DEBUG_STDOUT("PC [after]: " << (unsigned)Register.PC << std::endl);
            Clock.Tick(RTS_IMPLIED);
        default:
            break;
    }
}