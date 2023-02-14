// gcc -Wall -W -O0 -o prog1 prog1.c -lm
#define _GNU_SOURCE
#include <stdio.h> 
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sched.h>

// Size of a page in bytes
#define PAGE_SIZE 4192
#define NUM_TIMES 10000
#define MICROSECS_PER_SECOND 1000000
 
static inline uint64_t rdtsc() { 
    unsigned int eax, edx; 
    __asm__ __volatile__("rdtsc" : "=a" (eax), "=d" (edx)); 
    return ((uint64_t)edx << 32) | eax; 
}

// Used to determine current processor ID.
int get_cpu_id() {
    return sched_getcpu();
}

// Determine clock rate of the specified cpu.
int get_clock_rate(int cpu)
{
    char* filepath = malloc(strlen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq") + 10);
    uint32_t cycles_per_sec;
    snprintf(filepath, strlen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq") + 9, "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_cur_freq", cpu);
    FILE* file = fopen(filepath, "r");
    free(filepath);
    if (file == NULL) {
        printf("Error: could not open file to check cpu frequency\n");
        return -1;
    }
    fscanf(file, "%d", &cycles_per_sec);
    fclose(file);
    return cycles_per_sec;
}

int main() { 
    uint64_t start;
    uint64_t end;
    uint32_t elapsed;
    float* arr = malloc(NUM_TIMES * sizeof(float));
    char* ptr;
    for (int i = 0; i < NUM_TIMES; i++)
    {
        ptr = malloc(PAGE_SIZE);
        start = rdtsc(); 
        ptr[0] = 'a';
        end = rdtsc(); 
        elapsed = end - start;
        // Convert to microseconds and store in array
        float microseconds = (double)elapsed * MICROSECS_PER_SECOND / get_clock_rate(get_cpu_id());
        arr[i] = microseconds;
    }
    // Calculate statistics (max, min, avg, stddev)
    double sum;
    double min;
    double max;
    double avg;
    double stddev; 
    for (int i = 0; i < NUM_TIMES; i++)
    {
        sum += arr[i];

        if(arr[i] <= min){
            min = arr[i];
        }

        if(arr[i] >= max){
            max = arr[i];
        }
    }
    
    avg = sum / NUM_TIMES;

    for(int i = 0; i < NUM_TIMES; i++)
    {
        stddev += pow(arr[i] - avg, 2);
    }
    free(arr);
    stddev = sqrt(stddev / NUM_TIMES);
    // Print statistics
    printf("Latency stats for %d soft page faults:\n", NUM_TIMES);
    printf("Maximum: %0.2f us\n", max);
    printf("Minimum: %0.2f us\n", min);
    printf("Average: %0.2f us\n", avg);
    printf("Standard Deviation: %0.2f\n", stddev);
    return 0;
} 