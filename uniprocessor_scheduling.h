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
    int min = -1;
    int temp; // for comparing to min value
    int iter; // Keep track of running process
    int processEndFlag = 0; // 1 if a process just ended
    int endFlag = 0; // 1 if needs to end
    int finishedProcesses = 0; 
    while(!endFlag)
    //for(int a = 0; a < 25; a++)
    {
        finishedProcesses = 0; // Reset 
        for(int i = 0; i < NUM_PROCESSES; i++) // Iterate through processes
        {
            if(clk == processes[i]->arrival || processEndFlag == 1) // New process just arrived, time to change order
            {
                processEndFlag = 0; // Reset flag
                processes[i]->arrived = 1; // Flip arrived flag
            }
            if(processes[i]->arrived == 1 && !processes[i]->finished) // If process has arrived and not finished, and it is not the first process to be checked
            {
                if (min == -1) // Valid min value not found yet
                {
                    min = processes[i]->service;
                    iter = i;
                }
                if(min > processes[i]->service) // Replace min if necessary
                {
                    min = processes[i]->service;
                    iter = i;
                    
                }
            }
            // Check for number of finished processes
            if(processes[i]->finished) finishedProcesses++; // Increment 
            
        }
        if (finishedProcesses == NUM_PROCESSES) 
            return; // Program is done, safe to exit

        //printf("Running process: %s, arrival time %d, service Time %d.\n", 
            //processes[iter]->name, processes[iter]->arrival, processes[iter]->service);
        for(int i = 0; i < NUM_PROCESSES; i++) // Iterate through each process
        {
            if (i == iter) // If selected to run
            {
                processes[i]->running = 1;
                if(!processes[i]->started) // If process has not started
                {
                    processes[i]->started = 1;
                    processes[i]->startTime = clk;
                    processes[i]->waitTime = processes[i]->startTime - processes[i]->arrival; // Wait time
                }
                processes[i]->service--; // Decrement service time, count as ran
                
                if (processes[i]->service <=0) // If processes finished executing
                {
                    // Calc finish time and turnaround time
                    processes[i]->finishTime = clk + 1; // Clk not incremented yet, must add one to compensate
                    processes[i]->turnaroundTime = processes[i]->finishTime - processes[i]->arrival; // Turnaround time
                    processes[i]->finished = 1;
                    processes[i]->running = 0;
                    processEndFlag = 1;
                }
                
            }
            else // Not selected to run 
            {
                processes[i]->running = 0;
            }
        }
        if(endFlag) 
            return;
        clk++; // Increment clock
        min = -1;    
    }
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

void FCFS(struct process** processes){
  processes[0]->startTime = processes[0]->arrival;
  processes[0]->finishTime = processes[0]->service;
  processes[0]->waitTime = 0;
  processes[0]->turnaroundTime = processes[0]->service;

  for (int i = 1; i < NUM_PROCESSES; i++){
    processes[i]->startTime = processes[i-1]->finishTime;
    processes[i]->finishTime = processes[i]->startTime + processes[i]->service;
    processes[i]->waitTime = processes[i]->startTime - processes[i]->arrival;
    processes[i]->turnaroundTime = processes[i]->finishTime - processes[i]->arrival;
  }
}

void SPN(struct process** processes){
  struct process *temp;
  struct process *temp2;
  struct process *temp3;

  processes[0]->startTime = processes[0]->arrival;
  processes[0]->finishTime = processes[0]->service;
  processes[0]->waitTime = 0;
  processes[0]->turnaroundTime = processes[0]->service;


  for (int i = 1; i < NUM_PROCESSES - 1; i++){
    temp = processes[i];
    for (int j = i + 1; j < NUM_PROCESSES; j++){
      if(temp->service > processes[j]->service){
        temp3 = temp;
        temp = processes[j];
        processes[j] = temp3;
      }
    }

    temp2 = temp;
    temp = processes[i];
    processes[i] = temp2;
  }

  for (int i = 1; i < NUM_PROCESSES; i++){
    temp = processes[i];
    for (int j = i + 1; j < NUM_PROCESSES; j++){
      if(temp->arrival > processes[i-1]->finishTime){
        temp3 = temp;
        temp = processes[j];
        processes[j] = temp3;
      }
    }
    temp->startTime = processes[i-1]->finishTime;
    temp->finishTime = temp->startTime + temp->service;
    temp->waitTime = temp->startTime - temp->arrival;
    temp->turnaroundTime = temp->finishTime - temp->arrival;
    temp2 = temp;
    temp = processes[i];
    processes[i] = temp2;
  }
}
