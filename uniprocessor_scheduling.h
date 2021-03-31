#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PROCESSES 5
#define INPUT_FILE "inp2_lab7.txt"
#define OUTPUT_FILE "out2_lab7.txt"

struct process{
    char name[10];
    int arrival, service, startTime, finishTime, waitTime, turnaroundTime;
    int executionTime;
    int arrived, started, finished, running;
};


char* SRT(struct process** processes)
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
    char* processLog = (char*)malloc(50*sizeof(char));

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

        if (finishedProcesses == NUM_PROCESSES) // Check to see if all processes finished
        {
           break;
        } 

        for(int i = 0; i < NUM_PROCESSES; i++) // Iterate through each process
        {
            if (i == iter) // If selected to run
            {
                processLog[clk] = processes[i]->name[0];
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
        clk++; // Increment clock
        min = -1;    
    }
    strcat(processLog, "$"); // End char
    return processLog; // Everything executed, exit algorithm
    
}

void printGanttChartSRT(char* processLog)
{ // Prints a gantt chart of the SRT operation
    int numProcessorCycles = 0;
    for(int i = 0; i < 50; i++) // Find the end of the string
    {
        if (processLog[i] == '$')
        {
            numProcessorCycles = i;
        }
    }
    //Create arrays for each process, length based on how many processor cycles happened
    int A[numProcessorCycles];
    int B[numProcessorCycles];
    int C[numProcessorCycles];
    int D[numProcessorCycles];
    int E[numProcessorCycles];

    for(int i = 0; i < numProcessorCycles; i++) // Instantiate arrays to all zeroes
    {
        A[i] = 0;
        B[i] = 0;
        C[i] = 0;
        D[i] = 0;
        E[i] = 0;
    }

    for (int i = 0; i < numProcessorCycles; i++) // Switch arrays to 1 if process runs on that CPU cycle
    {
        switch(processLog[i])
        {
            case 'A':
                A[i] = 1;
                break;
            case 'B':
                B[i] = 1;
                break;
            case 'C':
                C[i] = 1;
                break;
            case 'D':
                D[i] = 1;
                break;
            case 'E':
                E[i] = 1;
                break;
        }
    }

    // Print statements for each array
    for(int i = 0; i < numProcessorCycles; i++) // Print A
    { 
        if(A[i] == 0)
            printf("  ");
        else
            printf("A ");
    }
    printf("\n");

    for(int i = 0; i < numProcessorCycles; i++) // Print B
    { 
        if(B[i] == 0)
            printf("  ");
        else
            printf("B ");
    }
    printf("\n");

    for(int i = 0; i < numProcessorCycles; i++) // C
    { 
        if(C[i] == 0)
            printf("  ");
        else
            printf("C ");
    }
    printf("\n");

    for(int i = 0; i < numProcessorCycles; i++) // D
    { 
        if(D[i] == 0)
            printf("  ");
        else
            printf("D ");
    }
    printf("\n");

    for(int i = 0; i < numProcessorCycles; i++) // E
    { 
        if(E[i] == 0)
            printf("  ");
        else
            printf("E ");
    }
    printf("\n");
    
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

  //print gantt chart
  for (int i = 0; i < processes[0]->service; i++){
    printf("%s ", processes[0]->name);
  }
  printf("\n");

  for (int i = 1; i < NUM_PROCESSES; i++){
    processes[i]->startTime = processes[i-1]->finishTime;
    processes[i]->finishTime = processes[i]->startTime + processes[i]->service;
    processes[i]->waitTime = processes[i]->startTime - processes[i]->arrival;
    processes[i]->turnaroundTime = processes[i]->finishTime - processes[i]->arrival;
  }

  //print gantt chart
  int count = processes[0]->service;
  for (int i = 1; i < NUM_PROCESSES; i++){
    for (int j = 0; j < count; j++){
      printf("  ");
    }
    for(int k = 0; k < processes[i]->service; k++){
      printf("%s ", processes[i]->name);
    }
    printf("\n");
    count += processes[i]->service;
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

  int totalTime = 0; //Time to finish
  for (int i = 0; i < NUM_PROCESSES; i++){
    totalTime = totalTime + processes[i]->service;
  }

  //print gantt chart
  for (int i = 0; i < processes[0]->service; i++){
    printf("%s ", processes[0]->name);
  }
  printf("\n");

  //Rearranging in service time
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

  //Rearranging in Arrival time
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



  //print gantt chart
  int count = processes[0]->service;
  for (int i = 1; i < NUM_PROCESSES; i++){
    for (int j = 0; j < count; j++){
      printf("  ");
    }
    for(int k = 0; k < processes[i]->service; k++){
      printf("%s ", processes[i]->name);
    }
    printf("\n");
    count += processes[i]->service;
  }
}
