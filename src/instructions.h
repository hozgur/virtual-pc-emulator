#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>

/*
Instruction encoding formats:

MOV (move immediate to register):
  31   24 23   16 15                0
  +-------+-------+-----------------+
  | 0x01  | reg   |   imm16         |
  +-------+-------+-----------------+
  [opcode][reg][immediate value]

ADD (add register to register):
  31   24 23   20 19   16 15        0
  +-------+-------+-------+---------+
  | 0x10  | src   | dst   |  unused |
  +-------+-------+-------+---------+
  [opcode][src][dst][unused]

CALL (call subroutine):
  31   24 23                        0
  +-------+-------------------------+
  | 0x32  |      address (24 bits)  |
  +-------+-------------------------+
  [opcode][address]

RET (return from subroutine):
  31   24 23                        0
  +-------+-------------------------+
  | 0x33  |      unused             |
  +-------+-------------------------+
  [opcode][unused]

HLT (halt):
  31   24 23                        0
  +-------+-------------------------+
  | 0xFF  |      unused             |
  +-------+-------------------------+
  [opcode][unused]
*/

// Instruction opcodes
#define OP_MOV  0x01
#define OP_ADD  0x10
#define OP_CALL 0x32
#define OP_RET  0x33
#define OP_HLT  0xFF

// Register indices
#define REG_X   0
#define REG_Y   1
#define REG_Z   2
#define REG_A   3

// Helper macros for instruction encoding
#define ENCODE_MOV(reg, imm16)  ((OP_MOV << 24) | ((reg) << 16) | (imm16))
#define ENCODE_ADD(dst, src)    ((OP_ADD << 24) | (((src) << 4) | (dst)) << 16)
#define ENCODE_CALL(addr24)     ((OP_CALL << 24) | (addr24))
#define ENCODE_RET()            (OP_RET << 24)
#define ENCODE_HLT()            (OP_HLT << 24)

#endif // INSTRUCTIONS_H 