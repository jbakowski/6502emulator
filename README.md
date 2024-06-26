# 6502 Emulator<br/>

## Goal of the project<br/>

The goal of the project is to learn more about computer architecture by emulating a 6502 processor with proper cycle timings (although clock frequency can't be accurately emulated).<br/>

## Building the project<br/>

To compile the project, run the following command in user terminal:<br/>

```python build.py -msvc```<br/>

To compile and run the project, run the following command in user terminal:<br/>

```python build.py -msvc -run```<br/>

To clean the build directory, run the following command in user terminal:<br/>

```python build.py -clean```<br/>

## Debug mode<br/>

In order to turn on extensive debug logging, uncomment the DEBUG_MODE define present in 6502.hpp file.<br/>

## Implemented instructions

All instructions in Opcodes.h with a ```// implemented``` comment are implemented.<br/>

All LOAD / STORE operations with an immediate addressing mode are implemented.<br/>
All REGISTER TRANSFERS operations are implemented.<br/>
All STACK OPERATIONS are implemented.<br/>
All LOGICAL operations with an immediate addressing mode are implemented.<br/>
All ARITHMETIC operations with an immediate addressing mode are implemented.<br/>
All INC / DEC operations with an implied addressing mode are implemented.<br/>
All SHIFT operations with an accumulator addressing mode are implemented.<br/>
All JUMPS operations with an absolute/implied addressing mode are implemented.<br/>
All BRANCHES operations are implemented.<br/>
All STATUS FLAG CHANGES operations are implemented.<br/>

## Miscellaneous<br/>

### Default program

By default the processor runs a program calculating N-th Fibonacci number and storing the result in ACC. To calculate N-th Fibonacci number of your choosing - change the ```desiredNumber``` variable to a value between 1 and 7.

### Asserts<br/>

  
Emulator asserts if the stack pointer crosses the boundary of the fixed stack location (0x0100 / 0x01FF).<br/>

Emulator does not assert if any R/W operation is to be performed outside of the defined memory region, because the maximum value of the Program Counter variable is the maximum memory address (uint16_t / 0xFFFF) and it is not possible to perform R/W operations outside of the simulated memory.


### Stack<br/>

 Pushing data onto the stack puts the data onto the stack first and then decrements the stack pointer.<br/>
 Popping data from the stack increments the stack pointer first and then pulls the data from the stack.

## Possible further additions<br/>

Implementing a way to load in a binary file containing program data to be run by the emulated processor.<br/>
Implementing a parser written in Python decoding a file with assembly code and turning it into a binary file to be loaded into the processor's memory.


  
