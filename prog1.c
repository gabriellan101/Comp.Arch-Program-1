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
    uint64_t start = rdtsc(); 
    // code to be timed
    char* ptr = malloc(4192);
    ptr[0] = 0x8;
    // ************ 
    uint64_t end = rdtsc(); 
    uint64_t elapsed = end - start; 
    printf("Elapsed time: %lu cycles\n", elapsed);
    // Convert to seconds
    double microseconds = elapsed * 1000000 / (float)CLOCKS_PER_SEC;
    printf("With %lu clocks per second, this equals %f microseconds\n", CLOCKS_PER_SEC, microseconds);
    return 0; 
} 