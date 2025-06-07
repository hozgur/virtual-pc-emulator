#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "emulator.h"
#include "memory_map.h"
// Forward declaration from video_controller.c
void video_tick();

static uint32_t* reg_ptr(CPU* cpu, uint8_t idx) {
    switch(idx) {
        case 0: return &cpu->X;
        case 1: return &cpu->Y;
        case 2: return &cpu->Z;
        case 3: return &cpu->A;
        default: return NULL;
    }
}

static uint32_t fetch32(uint32_t addr) {
    return memory[addr] |
           (memory[addr + 1] << 8) |
           (memory[addr + 2] << 16) |
           (memory[addr + 3] << 24);
}

static void push32(CPU* cpu, uint32_t value) {
    cpu->SP -= 4;
    memory[cpu->SP]     = value & 0xFF;
    memory[cpu->SP + 1] = (value >> 8) & 0xFF;
    memory[cpu->SP + 2] = (value >> 16) & 0xFF;
    memory[cpu->SP + 3] = (value >> 24) & 0xFF;
}

static uint32_t pop32(CPU* cpu) {
    uint32_t value = memory[cpu->SP] |
                     (memory[cpu->SP + 1] << 8) |
                     (memory[cpu->SP + 2] << 16) |
                     (memory[cpu->SP + 3] << 24);
    cpu->SP += 4;
    return value;
}

void* execute(void* arg) {
    CPU* cpu = (CPU*)arg;
    int running = 1;
    while (running) {
        uint32_t instr = fetch32(cpu->PC);
        cpu->PC += 4;

        uint8_t opcode = (instr >> 24) & 0xFF;
        uint8_t b1 = (instr >> 16) & 0xFF;
        uint8_t b2 = (instr >> 8) & 0xFF;
        uint8_t b3 = instr & 0xFF;

        switch (opcode) {
            case 0x01: { // MOV reg, imm16
                uint8_t dst = b1;
                uint32_t imm = (b2 << 8) | b3;
                uint32_t* reg = reg_ptr(cpu, dst);
                if (reg) *reg = imm;
                break;
            }
            case 0x10: { // ADD dest, src
                uint8_t src = b1 >> 4;
                uint8_t dst = b1 & 0x0F;
                uint32_t* rsrc = reg_ptr(cpu, src);
                uint32_t* rdst = reg_ptr(cpu, dst);
                if (rsrc && rdst) *rdst += *rsrc;
                break;
            }
            case 0x32: { // CALL addr24
                uint32_t addr = (b1 << 16) | (b2 << 8) | b3;
                push32(cpu, cpu->PC);
                cpu->PC = addr;
                break;
            }
            case 0x33: { // RET
                cpu->PC = pop32(cpu);
                break;
            }
            case 0xFF: // HLT
                running = 0;
                break;
            default:
                printf("Unknown opcode: 0x%02X\n", opcode);
                running = 0;
                break;
        }

        video_tick();
    }
    return NULL;
}
