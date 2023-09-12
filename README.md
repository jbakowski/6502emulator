"# 6502emulator" 


## Stack

PushToStack: store-then-decrement
PopFromStack: increment-then-read

## Asserts

Emulator asserts if the stack pointer crosses the boundary of the fixed stack location (0x0100 / 0x01FF).

Emulator does not assert if any R/W operation is to be performed outside of the defined memory region, because the maximum value of the Program Counter variable is the maximum memory address (uint16_t / 0xFFFF) and it is not possible to perform R/W operations outside of the simulated memory.