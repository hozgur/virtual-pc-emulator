#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "emulator.h"
#include "memory_map.h"
#include "instructions.h"
// Forward declaration from video_controller.c
void video_tick();

extern uint8_t memory[MEM_SIZE];

static uint32_t fetch32(CPU* cpu) {
    uint32_t value = *(uint32_t*)&memory[cpu->PC];
    cpu->PC += 4;
    return value;
}

static void push32(CPU* cpu, uint32_t value) {
    cpu->SP -= 4;
    *(uint32_t*)&memory[cpu->SP] = value;
}

static uint32_t pop32(CPU* cpu) {
    uint32_t value = *(uint32_t*)&memory[cpu->SP];
    cpu->SP += 4;
    return value;
}

void execute(CPU* cpu) {
    while (1) {
        uint32_t instruction = fetch32(cpu);
        uint8_t opcode = instruction >> 24;
        uint32_t operand = instruction & 0xFFFFFF;

        switch (opcode) {
            case OP_MOV: {
                uint8_t reg = (instruction >> 16) & 0xFF;
                uint16_t imm16 = instruction & 0xFFFF;
                cpu->regs[reg] = imm16;
                break;
            }
            case OP_ADD: {
                uint8_t dst = (instruction >> 16) & 0x0F;
                uint8_t src = (instruction >> 20) & 0x0F;
                cpu->regs[dst] += cpu->regs[src];
                break;
            }
            case OP_CALL: {
                push32(cpu, cpu->PC);
                cpu->PC = operand;
                break;
            }
            case OP_RET: {
                cpu->PC = pop32(cpu);
                break;
            }
            case OP_HLT:
                return;
            default:
                printf("Unknown opcode: 0x%02X\n", opcode);
                return;
        }

        video_tick();
    }
}
