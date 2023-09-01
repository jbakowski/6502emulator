#include <6502.hpp>

void CPU::Reset(Memory &Memory) {
    // read address from POWER_ON_RESET
    // jump to the address
    // activate the routine
};

void Memory::Init() {
    for(uint32_t i = 0; i < MEM_MAX; i++) {
        Data[i] = 0;
    }
}