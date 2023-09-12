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

## Miscellaneous<br/>

### Asserts<br/>

  
Emulator asserts if the stack pointer crosses the boundary of the fixed stack location (0x0100 / 0x01FF).<br/>

Emulator does not assert if any R/W operation is to be performed outside of the defined memory region, because the maximum value of the Program Counter variable is the maximum memory address (uint16_t / 0xFFFF) and it is not possible to perform R/W operations outside of the simulated memory.


### Stack<br/>

 Pushing data onto the stack puts the data onto the stack first and then decrements the stack pointer.<br/>
 Popping data from the stack increments the stack pointer first and then pulls the data from the stack.
