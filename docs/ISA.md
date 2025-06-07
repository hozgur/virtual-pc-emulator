# Virtual PC Instruction Set Architecture (ISA)

## Overview
The Virtual PC uses a 32-bit instruction format with 24-bit addressing capability. Each instruction is encoded in a single 32-bit word, with the opcode occupying the most significant byte (bits 31-24).

## Register Set
- `X` (Register 0): General purpose register
- `Y` (Register 1): General purpose register
- `Z` (Register 2): General purpose register
- `A` (Register 3): Accumulator register
- `PC`: Program Counter (32-bit)
- `SP`: Stack Pointer (32-bit)
- `STATUS`: Status register (8-bit)

## Instruction Formats

### 1. MOV (Move Immediate)
Loads a 16-bit immediate value into a register.

```
31   24 23   16 15                0
+-------+-------+-----------------+
| 0x01  | reg   |   imm16         |
+-------+-------+-----------------+
[opcode][reg][immediate value]
```

Example:
```c
MOV A, 10    // Loads 10 into register A
```

### 2. ADD (Add Registers)
Adds the value of source register to destination register.

```
31   24 23   20 19   16 15        0
+-------+-------+-------+---------+
| 0x10  | src   | dst   |  unused |
+-------+-------+-------+---------+
[opcode][src][dst][unused]
```

Example:
```c
ADD A, Z     // Adds value in Z to A
```

### 3. CALL (Call Subroutine)
Calls a subroutine at the specified 24-bit address.

```
31   24 23                        0
+-------+-------------------------+
| 0x32  |      address (24 bits)  |
+-------+-------------------------+
[opcode][address]
```

Example:
```c
CALL 0x18    // Calls subroutine at address 0x18
```

### 4. RET (Return from Subroutine)
Returns from a subroutine to the calling location.

```
31   24 23                        0
+-------+-------------------------+
| 0x33  |      unused             |
+-------+-------------------------+
[opcode][unused]
```

Example:
```c
RET          // Returns from subroutine
```

### 5. HLT (Halt)
Stops the processor execution.

```
31   24 23                        0
+-------+-------------------------+
| 0xFF  |      unused             |
+-------+-------------------------+
[opcode][unused]
```

Example:
```c
HLT          // Halts the processor
```

## Memory Layout
- Program memory: 0x000000 - 0xFFFFFF (24-bit address space)
- Stack: Grows downward from end of memory
- Video RAM: 80x25 text mode display at VRAM_START

## Status Register Bits
- Bit 0: Zero flag (Z)
- Bit 1: Carry flag (C)
- Bit 2: Overflow flag (V)
- Bit 3: Negative flag (N)
- Bits 4-7: Reserved

## Examples

### Basic Program Flow
```c
MOV A, 10    // A = 10
CALL 0x18    // Call subroutine
HLT          // Stop

// Subroutine at 0x18
MOV Z, 5     // Z = 5
ADD A, Z     // A = A + Z
RET          // Return
```

### Stack Usage
The stack pointer (SP) is initialized to the end of memory and grows downward. Each PUSH operation decrements SP by 4 bytes, and each POP operation increments SP by 4 bytes.

## Implementation Notes
- All instructions are 32 bits wide
- Memory is byte-addressable but instructions must be aligned on 4-byte boundaries
- Register values are 32 bits wide
- Immediate values in MOV instructions are 16 bits wide
- Addresses in CALL instructions are 24 bits wide 