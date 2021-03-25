#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PROCESSES 5
#define INPUT_FILE "inp1_lab7.txt"
#define OUTPUT_FILE "out1_lab7.txt"

struct process{
    char name[10];
    int arrival, service, startTime, finishTime, waitTime, turnaroundTime;
    int executionTime;
    int arrived, started, finished, running;
};


void SRT(struct process** processes)
// Function: min[service time - time spent in execution] 
// Checks at arrival to update
{
    int clk = 0; // Clock
    int min = 10;
    int temp; // for comparing to min value
    int iter; // Keep track of running process

    for(int i = 0; i < NUM_PROCESSES; i++)
    {
        if(clk == processes[i]->arrival)
        {
            processes[i]->arrived = 1;
        }
        if(processes[i]->arrived == 1 && !processes[i]->finished && i > 0)
        {
            temp = processes[i]->service - processes[i]->executionTime;
            if(min > temp)
            {
                min = temp;
                iter = i;
            }
        }
    }
    //for(int i = 0; i < NUM_PROCESSES; i++)
    

}

void printResults(struct process** processes)
{
    printf("Process\tArrival Time\tService Time\tStart Time\tFinish Time\tWait Time\tTurnaround Time\n");
    for(int i = 0; i < NUM_PROCESSES; i++)
    {
        printf("%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            processes[i]->name,
            processes[i]->arrival,
            processes[i]->service,
            processes[i]->startTime,
            processes[i]->finishTime,
            processes[i]->waitTime,
            processes[i]->turnaroundTime);
    }
}