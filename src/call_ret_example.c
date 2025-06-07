#include <stdint.h>
#include <string.h>
#include "emulator.h"
#include "memory_map.h"

void load_call_ret_example() {
    cores[0].Z = 5;
    cores[0].SP = MEM_SIZE - 0x1000;
    cores[0].PC = 0x0000;

    uint32_t program[] = {
        0x0103000A, // MOV A, 10
        0x3200000C, // CALL 0x000C
        0xFF000000, // HLT
        0x10230200, // ADD A, Z
        0x33000000  // RET
    };

    memcpy(&memory[0x0000], program, sizeof(program));
}
