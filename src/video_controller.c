#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "memory_map.h"
#include "emulator.h"

#define SCREEN_WIDTH  80
#define SCREEN_HEIGHT 25
#define TEXT_BUFFER_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)

static char text_buffer[TEXT_BUFFER_SIZE];

void video_reset() {
    memset(&memory[VRAM_START], ' ', VRAM_SIZE);
    memset(text_buffer, ' ', TEXT_BUFFER_SIZE);
    *(uint32_t*)&memory[VIDEO_MODE_REG] = 1;
}

void video_write_char(uint32_t x, uint32_t y, char c) {
    if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT) return;
    uint32_t offset = y * SCREEN_WIDTH + x;
    memory[VRAM_START + offset] = (uint8_t)c;
    text_buffer[offset] = c;
}

void video_render_text_terminal() {
    printf("\033[H");
    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            putchar(text_buffer[y * SCREEN_WIDTH + x]);
        }
        putchar('\n');
    }
}

void video_tick() {
    if (*(uint32_t*)&memory[VIDEO_MODE_REG] == 1) {
        memcpy(text_buffer, &memory[VRAM_START], TEXT_BUFFER_SIZE);
    }
}
