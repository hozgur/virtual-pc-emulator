#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#define RAM_START         0x000000
#define RAM_SIZE          0x100000
#define VRAM_START        0x100000
#define VRAM_SIZE         0x010000
#define IO_REG_START      0x200000
#define IO_REG_SIZE       0x010000
#define ROM_START         0x300000
#define ROM_SIZE          0x100000

#define VIDEO_MODE_REG    (IO_REG_START + 0x0000)
#define VIDEO_STATUS_REG  (IO_REG_START + 0x0004)
#define VIDEO_FB_START    VRAM_START
#define KEYBOARD_DATA_REG (IO_REG_START + 0x0010)
#define TIMER_FLAG_REG    (IO_REG_START + 0x0020)
#define DISK_DATA_PORT    (IO_REG_START + 0x0100)

#endif // MEMORY_MAP_H
