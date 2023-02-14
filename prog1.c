// gcc -Wall -W -O0 -std=c11 -o prog1 prog1.c
#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

    //need to report:
    // 1. maximum
    //array of ints is the set of 10,000
    //for loop probs for max and min and average 
    //int max;
    // 2. minimum 
    // 3. average 
    // 4. std dev across 10,000 soft page faults 

    for (int i = 0; i < NUM_TIMES; i++){
        float sum = 0.0;
        float min = 0.0;
        float max = 0.0;
        float avg = 0.0;
        float stddev = 0.0;

        sum += arr[i];

        if(min >= arr[i]){
            min = arr[i];
        }

        if(max <= arr[i]){
            max = arr[i];
        }

        avg = sum / NUM_TIMES;

        for(i = 0; i < NUM_TIMES; i++){

            stddev += pow(arr[i] - avg, 2);

        }
        //not sure about this 
        //still need to add print statements 

        stddev = sqrt(stddev / NUM_TIMES);



    }

    return 0;
} 