// cycles for fundamental processor operations (memory R/W, stack POP/PUSH, etc)

#define FETCH_BYTE_CYCLE 2

// LDA - Load Accumulator

#define LDA_IMMEDIATE           0xA9
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

#define LDX_IMMEDIATE           0xA2
#define LDX_IMMEDIATE_CYCLE     2

#define LDX_ZERO_PAGE           0xA6
#define LDX_ZERO_PAGE_CYCLE     3

#define LDX_ZERO_PAGE_Y         0xB6
#define LDX_ZERO_PAGE__Y_CYCLE     4

#define LDX_ABSOLUTE            0xAE
#define LDX_ABSOLUTE_CYCLE      4

#define LDX_ABSOLUTE_Y          0xBE
#define LDX_ABSOLUTE_Y_CYCLE    4