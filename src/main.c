#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emulator.h"
#include "memory_map.h"

extern void load_call_ret_example(void);
extern void* execute(void*);
extern void video_reset(void);
extern void video_render_text_terminal(void);

uint8_t memory[MEM_SIZE];
CPU cores[CORE_COUNT];

int main(void) {
    // Initialize memory
    memset(memory, 0, MEM_SIZE);

    // Initialize CPU
    memset(&cores[0], 0, sizeof(CPU));
    cores[0].PC = 0;  // Start execution at address 0
    cores[0].SP = MEM_SIZE;  // Stack grows downward from end of memory
    cores[0].id = 0;

    // Load the example program
    load_call_ret_example();

    // Execute the program
    execute(&cores[0]);

    // Print the final value of register A
    printf("A = %d\n", cores[0].regs[3]);

    return 0;
}
