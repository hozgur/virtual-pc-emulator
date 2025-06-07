#include <stdio.h>
#include <string.h>
#include "emulator.h"
#include "memory_map.h"

extern void load_call_ret_example(void);
extern void* execute(void*);

uint8_t memory[MEM_SIZE];
CPU cores[CORE_COUNT];

int main() {
    load_call_ret_example();

    printf("Program çalıştırılıyor...\n");
    execute(&cores[0]);

    printf("Program sona erdi. A = %u\n", cores[0].A);
    return 0;
}
