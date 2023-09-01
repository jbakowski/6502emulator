//#ifndef 6502_H
//#define 6502_H
#include <stdint.h>

#define MEM_MAX 0xFFFF                        // 6502 processor is capable of addressing at most 64Kb of memory via 16-bit address bus

// special addresses
#define NON_MASKABLE_INTERRUPT_HANDLER 0xFFFA // 2 bytes long
#define POWER_ON_RESET                 0xFFFC // 2 bytes long
#define IRQ_HANDLER                    0xFFFE // 2 bytes long

#define STACK_START                    0x0100 // 256 byte stack, fixed location
#define STACK_END                      0x01FF
class CPU {

    // registers
    struct Register {
    uint16_t    PC;  // program counter
    uint8_t     SP;  // stack pointer - pushing bytes onto the stack causes the stack pointer to be decremented
    uint8_t     ACC; // accumulator
    uint8_t     IRX; // index register X
    uint8_t     IRY; // index register Y
    };

    // processor status flags

    struct StatusFlag {
        uint8_t C : 1;  // carry
        uint8_t Z : 1;  // zero
        uint8_t I : 1;  // interrupt disable
        uint8_t D : 1;  // decimal mode
        uint8_t B : 1;  // break
        uint8_t O : 1;  // overflow
        uint8_t N : 1;  // negative
    };

    void Reset(Memory &Memory);
    void ExecuteInstruction(Memory &Memory);

};

class Memory {
    uint8_t Data[MEM_MAX];

    void Init();
};

class Clock {
    uint32_t ClockFrequency;
    
};
//#endif