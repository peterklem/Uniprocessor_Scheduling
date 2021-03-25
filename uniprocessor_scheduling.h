#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PROCESSES 5
#define INPUT_FILE "inp1_lab7.txt"
#define OUTPUT_FILE "out1_lab7.txt"

struct process{
    char name[10];
    int arrival, service, startTime, finishTime, waitTime, turnaroundTime;
};

void SRT(struct process* processes)
{
    //    
}

void printResults(struct process* processes)
{
    for(int i = 0; i < NUM_PROCESSES; i++)
    {
        
    }
}