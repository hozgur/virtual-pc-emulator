#ifndef EMULATOR_H
#define EMULATOR_H

#include <stdint.h>
#ifdef _WIN32
typedef struct { int unused; } pthread_mutex_t;
#else
#include <pthread.h>
#endif

#define MEM_SIZE (1 << 24)
#define CORE_COUNT 2
#define MESSAGE_QUEUE_SIZE 16

extern uint8_t memory[MEM_SIZE];

typedef struct {
    uint32_t messages[MESSAGE_QUEUE_SIZE];
    int head;
    int tail;
    pthread_mutex_t lock;
} MessageQueue;

typedef struct {
    uint32_t X, Y, Z, A;
    uint32_t PC;
    uint32_t SP;
    uint8_t STATUS;
    int id;
    MessageQueue mq;
} CPU;

extern CPU cores[CORE_COUNT];

#endif // EMULATOR_H
