#include <stdint.h>
#include "memory_map.h"
#include "emulator.h"
#include "instructions.h"

extern uint8_t memory[MEM_SIZE];

void load_call_ret_example(void) {
    // Define the string in memory
    const char* message = "Hello, Virtual PC!";
    uint32_t message_addr = 0x2000; // Place the string at this address
    for (int i = 0; message[i] != '\0'; i++) {
        memory[message_addr + i] = message[i];
    }

    // Machine code to write the string to the screen
    uint32_t screen_addr = VRAM_START + 30 * 80 + 15; // Starting position on screen
    uint32_t i = 0;
    while (message[i] != '\0') {
        memory[screen_addr + i] = message[i];
        i++;
    }

    // Original program code
    *(uint32_t*)&memory[0] = ENCODE_MOV(REG_A, 10);    // MOV A, 10
    *(uint32_t*)&memory[4] = ENCODE_CALL(0x18);        // CALL 0x18 (24 in decimal)
    *(uint32_t*)&memory[8] = ENCODE_HLT();             // HLT

    // Subroutine at offset 24
    *(uint32_t*)&memory[24] = ENCODE_MOV(REG_Z, 5);    // MOV Z, 5
    *(uint32_t*)&memory[28] = ENCODE_ADD(REG_A, REG_Z);// ADD A, Z
    *(uint32_t*)&memory[32] = ENCODE_RET();            // RET
}
