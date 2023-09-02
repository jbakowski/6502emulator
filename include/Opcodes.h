// cycles for fundamental processor operations (memory R/W, stack POP/PUSH, etc)

#define FETCH_BYTE_CYCLE 2

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
#define LDX_ZERO_PAGE_Y_CYCLE  4

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

#define STA_ZERO_PAGE           0x85    // implemented
#define STA_ZERO_PAGE_CYCLE     3

#define STA_ZERO_PAGE_X         0x95
#define STA_ZERO_PAGE_X_CYCLE   4

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

#define STX_ZERO_PAGE           0x86    // implemented
#define STX_ZERO_PAGE_CYCLE     3

#define STX_ZERO_PAGE_Y         0x96
#define STX_ZERO_PAGE_Y_CYCLE   4

#define STX_ABSOLUTE            0x8E
#define STX_ABSOLUTE_CYCLE      4

// STY - Store Y Register

#define STY_ZERO_PAGE           0x84    // implemented
#define STY_ZERO_PAGE_CYCLE     3

#define STY_ZERO_PAGE_X         0x94
#define STY_ZERO_PAGE_X_CYCLE   4

#define STY_ABSOLUTE            0x8C
#define STY_ABSOLUTE_CYCLE      4

// ###############################
// ###   REGISTER TRANSFERS    ###
// ###############################

// TAX - Transfer Accumulator to X

#define TAX_IMPLIED             0xAA    // implemented

// TAY - Transfer Accumulator to Y

#define TAY_IMPLIED             0xA8    // implemented

// TXA - Transfer X to Accumulator

#define TXA_IMPLIED             0x8A    // implemented

// TYA - Transfer Y to Accumulator

#define TYA_IMPLIED             0x98    // implemented

// ###############################
// ###    STACK  OPERATIONS    ###
// ###############################

// TSX - Transfer Stack Pointer to X

#define TSX_IMPLIED             0xBA

// TXA - Transfer X to Accumulator

#define TXA_IMPLIED             0x8A

// PHA - Push Accumulator

#define PHA_IMPLIED             0x48

// PHP - Push Processor Status

#define PHP_IMPLIED             0x08

// PLA - Pull Accumulator

#define PLA_IMPLIED             0x68

// PLP - Pull Processor

#define PLP_IMPLIED             0x28

// ###############################
// ###         LOGICAL         ###
// ###############################

// AND - Logcial AND

#define AND_IMMEDIATE           0x29



// ###############################
// ###     INC/DECREMENTS      ###
// ###############################

// ###############################
// ###         SHIFTS          ###
// ###############################

// ###############################
// ###          JUMPS          ###
// ###############################

// ###############################
// ###        BRANCHES         ###
// ###############################

// ###############################
// ###   STATUS FLAG CHANGES   ###
// ###############################

// ###############################
// ###     SYSTEM FUNCTIONS    ###
// ###############################