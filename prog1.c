// gcc -Wall -W -O0 -std=c11 -o prog1 prog1.c
#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h>
#include <time.h> 
 
static inline uint64_t rdtsc() { 
    unsigned int eax, edx; 
    __asm__ __volatile__("rdtsc" : "=a" (eax), "=d" (edx)); 
    return ((uint64_t)edx << 32) | eax; 
}

int main() { 
    for (int i = 0; i < 10000; i++)
    {
        char* ptr = malloc(4192);
        uint64_t start = rdtsc(); 
        ptr[0] = 0x8;
        uint64_t end = rdtsc(); 
        uint64_t elapsed = end - start; 
        // Convert to microseconds
        int microseconds = elapsed * 1000000 / (float)CLOCKS_PER_SEC;
        printf("%d microseconds\n", microseconds);
    }
    return 0;
} 