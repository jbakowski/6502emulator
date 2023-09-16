#ifndef OPCODES_H
#define OPCODES_H
// not all instructions have a constant cycle count (branch instructions or accessing memory across pages, for example)
// therefore, the listed cycle count is the minimal count for a given opcode
// extra cycles, if needed, ought to be added in the instruction implementation

// ###############################
// ### LOAD / STORE OPERATIONS ###
// ###############################

// LDA - Load Accumulator

#define LDA_IMMEDIATE           0xA9 // implemented
#define LDA_IMMEDIATE_CYCLE     2

#define LDA_ZERO_PAGE           0xA5
#define LDA_ZERO_PAGE_CYCLE     3

#define LDA_ZERO_PAGE_X         0xB5
#define LDA_ZERO_PAGE_X_CYCLE   4

#define LDA_ABSOLUTE            0xAD
#define LDA_ABSOLUTE_CYCLE      4

#define LDA_ABSOLUTE_X          0xBD
#define LDA_ABSOLUTE_X_CYCLE    4

#define LDA_ABSOLUTE_Y          0xB9
#define LDA_ABSOLUTE_Y_CYCLE    4

#define LDA_INDIRECT_X          0xA1
#define LDA_INDIRECT_X_CYCLE    6  

#define LDA_INDIRECT_Y          0xB1
#define LDA_INDIRECT_Y_CYCLE    5

// LDX - Load X Register

#define LDX_IMMEDIATE           0xA2    // implemented
#define LDX_IMMEDIATE_CYCLE     2

#define LDX_ZERO_PAGE           0xA6
#define LDX_ZERO_PAGE_CYCLE     3

#define LDX_ZERO_PAGE_Y         0xB6
#define LDX_ZERO_PAGE_Y_CYCLE   4

#define LDX_ABSOLUTE            0xAE
#define LDX_ABSOLUTE_CYCLE      4

#define LDX_ABSOLUTE_Y          0xBE
#define LDX_ABSOLUTE_Y_CYCLE    4

// LDY - Load Y Register

#define LDY_IMMEDIATE           0xA0    // implemented
#define LDY_IMMEDIATE_CYCLE     2

#define LDY_ZERO_PAGE           0xA4
#define LDY_ZERO_PAGE_CYCLE     3

#define LDY_ZERO_PAGE_X         0xB4
#define LDY_ZERO_PAGE__X_CYCLE  4

#define LDY_ABSOLUTE            0xAC
#define LDY_ABSOLUTE_CYCLE      4

#define LDY_ABSOLUTE_X          0xBC
#define LDY_ABSOLUTE_X_CYCLE    4

// STA - Store Accumulator

#define STA_ZEROPAGE            0x85    // implemented
#define STA_ZEROPAGE_CYCLE      3

#define STA_ZEROPAGE_X          0x95
#define STA_ZEROPAGE_X_CYCLE    4

#define STA_ABSOLUTE            0x8D
#define STA_ABSOLUTE_CYCLE      4

#define STA_ABSOLUTE_X          0x9D
#define STA_ABSOLUTE_X_CYCLE    5

#define STA_ABSOLUTE_Y          0x99
#define STA_ABSOLUTE_Y_CYCLE    5

#define STA_INDIRECT_X          0x81
#define STA_INDIRECT_X_CYCLE    6

#define STA_INDIRECT_Y          0x91
#define STA_INDIRECT_Y_CYCLE    6

// STX - Store X Register

#define STX_ZEROPAGE            0x86    // implemented
#define STX_ZEROPAGE_CYCLE      3

#define STX_ZEROPAGE_Y          0x96
#define STX_ZEROPAGE_Y_CYCLE    4

#define STX_ABSOLUTE            0x8E
#define STX_ABSOLUTE_CYCLE      4

// STY - Store Y Register

#define STY_ZEROPAGE            0x84    // implemented
#define STY_ZEROPAGE_CYCLE      3

#define STY_ZEROPAGE_X          0x94
#define STY_ZEROPAGE_X_CYCLE    4

#define STY_ABSOLUTE            0x8C
#define STY_ABSOLUTE_CYCLE      4

// ###############################
// ###   REGISTER TRANSFERS    ###
// ###############################

// TAX - Transfer Accumulator to X

#define TAX_IMPLIED             0xAA    // implemented
#define TAX_IMPLIED_CYCLE       2

// TAY - Transfer Accumulator to Y

#define TAY_IMPLIED             0xA8    // implemented
#define TAY_IMPLIED_CYCLE       2

// TXA - Transfer X to Accumulator

#define TXA_IMPLIED             0x8A    // implemented
#define TXA_IMPLIED_CYCLE       2

// TYA - Transfer Y to Accumulator

#define TYA_IMPLIED             0x98    // implemented
#define TYA_IMPLIED_CYCLE       2

// ###############################
// ###    STACK  OPERATIONS    ###
// ###############################

// TSX - Transfer Stack Pointer to X

#define TSX_IMPLIED             0xBA    // implemented
#define TSX_IMPLIED_CYCLE       2

// TXS - Transfer X to Stack Pointer

#define TXS_IMPLIED             0x9A    // implemented
#define TXS_IMPLIED_CYCLE       2

// PHA - Push Accumulator

#define PHA_IMPLIED             0x48    // implemented
#define PHA_IMPLIED_CYCLE       3

// PHP - Push Processor Status

#define PHP_IMPLIED             0x08    // implemented
#define PHP_IMPLIED_CYCLE       3

// PLA - Pull Accumulator

#define PLA_IMPLIED             0x68    // implemented
#define PLA_IMPLIED_CYCLE       4

// PLP - Pull Processor

#define PLP_IMPLIED             0x28    // implemented
#define PLP_IMPLIED_CYCLE       4

// ###############################
// ###         LOGICAL         ###
// ###############################

// AND - Logcial AND

#define AND_IMMEDIATE           0x29 // implemented
#define AND_IMMEDIATE_CYCLE     2

// EOR - Exclusive OR

#define EOR_IMMEDIATE           0x49 // implemented
#define EOR_IMMEDIATE_CYCLE     2

// ORA - Logical Inclusive OR

#define ORA_IMMEDIATE           0x09 // implemented
#define ORA_IMMEDIATE_CYCLE     2

// BIT_TEST - Bit Test

#define BIT_TEST_ZEROPAGE       0x24
#define BIT_TEST_ZEROPAGE_CYCLE 3

// ###############################
// ###       ARITHMETIC        ###
// ###############################

// ADC - Add with Carry

#define ADC_IMMEDIATE           0x69 // implemented
#define ADC_IMMEDIATE_CYCLE     2

#define ADC_ZEROPAGE            0x65 // implemented
#define ADC_ZEROPAGE_CYCLE      3

// SBC - Subtract with Carry
#define SBC_IMMEDIATE           0xE9 // implemented
#define SBC_IMMEDIATE_CYCLE     2

// CMP - Compare

#define CMP_IMMEDIATE           0xC9 // implemented
#define CMP_IMMEDIATE_CYCLE     3

// CPX - Compare X Register

#define CPX_IMMEDIATE           0xE0 // implemented
#define CPX_IMMEDIATE_CYCLE     2

// CPY - Compare Y Register

#define CPY_IMMEDIATE           0xC0 // implemented
#define CPY_IMMEDIATE_CYCLE     2

// ###############################
// ###     INC/DECREMENTS      ###
// ###############################

// INC - Increment Memory

#define INC_ZEROPAGE            0xE6 // implemented
#define INC_ZEROPAGE_CYCLE      5

// INX - Increment X Register

#define INX_IMPLIED             0xE8 // implemented
#define INX_IMPLIED_CYCLE       2

// INY - Increment Y Register

#define INY_IMPLIED             0xC8 // implemented
#define INY_IMPLIED_CYCLE       2

// DEC - Decrement Memory

#define DEC_ZEROPAGE            0xC6 // implemented
#define DEC_ZEROPAGE_CYCLE      5

// DEX - Decrement X Register

#define DEX_IMPLIED             0xCA // implemented
#define DEX_IMPLIED_CYCLE       2

// DEY - Decrement Y Register

#define DEY_IMPLIED             0x88 // implemented
#define DEY_IMPLIED_CYCLE       2

// ###############################
// ###         SHIFTS          ###
// ###############################

// ASL - Arithmetic Shift Left

#define ASL_ACCUMULATOR         0x0A
#define ASL_ACCUMULATOR_CYCLE   2

// LSR - Logical Shift Right

#define LSR_ACCUMULATOR         0x4A
#define LSR_ACCUMULATOR_CYCLE   2

// ROL - Rotate Left

#define ROL_ACCUMULATOR         0x2A
#define ROL_ACCUMULATOR_CYCLE   2

// ROR - Rotate Right

#define ROR_ACCUMULATOR         0x6A
#define ROR_ACCUMULATOR_CYCLE   2

// ###############################
// ###          JUMPS          ###
// ###############################

// JMP - Jump

#define JMP_ABSOLUTE            0x4C // implemented
#define JMP_ABSOLUTE_CYCLE      3

// JSR - Jump to Subroutine

#define JSR_ABSOLUTE            0x20 // implemented
#define JSR_ABSOLUTE_CYCLE      6

// RTS - Return from Subroutine

#define RTS_IMPLIED             0x60 // implemented
#define RTS_IMPLIED_CYCLE       6

// ###############################
// ###        BRANCHES         ###
// ###############################

// BCC - Branch if Carry Clear

#define BCC_RELATIVE            0x90 // implemented
#define BCC_RELATIVE_CYCLE      2

// BCS - Branch if Carry Set

#define BCS_RELATIVE            0xB0 // implemented
#define BCS_RELATIVE_CYCLE      2

// BEQ - Branch if Equal

#define BEQ_RELATIVE            0xF0 // implemented
#define BEQ_RELATIVE_CYCLE      2

// BMI - Branch if Minus

#define BMI_RELATIVE            0x30 // implemented
#define BMI_RELATIVE_CYCLE      2

// BNE - Branch if Not Equal

#define BNE_RELATIVE            0xD0 // implemented
#define BNE_RELATIVE_CYCLE      2

// BPL - Branch if Positive

#define BPL_RELATIVE            0x10 // implemented
#define BPL_RELATIVE_CYCLE      2

// BVC - Branch if Overflow Clear

#define BVC_RELATIVE            0x50 // implemented
#define BVC_RELATIVE_CYCLE      2

// BVS - Branch if Overflow Set

#define BVS_RELATIVE            0x70 // implemented
#define BVS_RELATIVE_CYCLE      2

// ###############################
// ###   STATUS FLAG CHANGES   ###
// ###############################

// CLC - Clear Carry Flag

#define CLC_IMPLIED             0x18
#define CLC_IMPLIED_CYCLE       2

// CLD - Clear Decimal Mode

#define CLD_IMPLIED             0xD8
#define CLD_IMPLIED_CYCLE       2

// CLI - Clear Interrupt Mode

#define CLI_IMPLIED             0x58
#define CLI_IMPLIED_CYCLE       2

// CLV - Clear Overflow Flag

#define CLV_IMPLIED             0xB8
#define CLV_IMPLIED_CYCLE       2

// SEC - Set Carry Flag

#define SEC_IMPLIED             0x38
#define SEC_IMPLIED_CYCLE       2

// SED - Set Decimal Flag

#define SED_IMPLIED             0xF8
#define SED_IMPLIED_CYCLE       2

// SEI - Set Interrupt Disable

#define SEI_IMPLIED             0x78
#define SEI_IMPLIED_CYCLE       2

// ###############################
// ###     SYSTEM FUNCTIONS    ###
// ###############################
#endif