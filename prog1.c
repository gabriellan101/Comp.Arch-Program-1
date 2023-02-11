// gcc -Wall -W -O0 -std=c11 -o prog1 prog1.c
#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TIMES 10000
#define MICROSECS_PER_SECOND 1000000
 
static inline uint64_t rdtsc() { 
    unsigned int eax, edx; 
    __asm__ __volatile__("rdtsc" : "=a" (eax), "=d" (edx)); 
    return ((uint64_t)edx << 32) | eax; 
}

int main() { 
    int* arr = malloc(NUM_TIMES * sizeof(int));
    for (int i = 0; i < NUM_TIMES; i++)
    {
        char* ptr = malloc(4192);
        uint64_t start = rdtsc(); 
        ptr[0] = 0x8;
        uint64_t end = rdtsc(); 
        uint64_t elapsed = end - start; 
        // Convert to microseconds
        int microseconds = elapsed * MICROSECS_PER_SECOND / (float)CLOCKS_PER_SEC;
        arr[i] = microseconds;
    }
    // add statistics calculation here
    return 0;
} 