#include <stdint.h>

class CPU {
    
    // registers
    struct Register {
    uint16_t    PC;  // program counter
    uint8_t     SP;  // stack pointer
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

};