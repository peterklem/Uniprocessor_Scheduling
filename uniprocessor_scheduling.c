#include "uniprocessor_scheduling.h"

int main()
{
    char str[250]; // Temporarily holds lines from input file
    int* tempVal; // Stores casted chars as ints before putting in process struct
    char* tempChar; // Stores chars from file until placed in array
    FILE* file; // input file
    file = fopen(INPUT_FILE, "r");
    struct process *processes[NUM_PROCESSES];

    fgets(str, sizeof(str), file); // Get header line
    
    // Add values into process array
    for(int i = 0; i < NUM_PROCESSES; i++)
    {
        // Init new process
        struct process *newEntry;
        newEntry = (struct process*)malloc(sizeof(struct process));
        // Parse input file
        fgets(str, sizeof(str), file);
        tempChar = strtok(str, ",");
        strcpy(newEntry->name, tempChar);
        tempChar = strtok(NULL, ",");
        newEntry->arrival = atoi(tempChar);
        tempChar = strtok(NULL, ",");
        newEntry->service = atoi(tempChar);
        //Set values to negative so a definitive start and finish can be shown
        newEntry->startTime = -1;
        newEntry->finishTime = -1;
        newEntry->waitTime = -1;
        newEntry->executionTime = 0;
        //Set flags
        newEntry->arrived = 0;
        newEntry->started = 0;
        newEntry->finished = 0;
        newEntry->running = 0;
        newEntry->turnaroundTime = -1;
        processes[i] = newEntry;
        
    }
    printResults(processes);


    return 0;
}