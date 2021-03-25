#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PROCESSES 5
#define INPUT_FILE "inp1_lab7.txt"
#define OUTPUT_FILE "out1_lab7.txt"

struct process{
    char name[10];
    int arrival, service;
};

int main()
{
    char str[250]; // Temporarily holds lines from input file
    int* tempVal; // Stores casted chars as ints before putting in process struct
    char* tempChar; // Stores chars from file until placed in array
    FILE* file; // input file
    file = fopen(INPUT_FILE, "r");
    struct process* processes[NUM_PROCESSES];
    
    fgets(str, sizeof(str), file); // Get header line
    
    // Add values into process array
    for(int i = 0; i < NUM_PROCESSES; i++)
    {
        processes[i] = (struct process*)malloc(sizeof(struct process));
        fgets(str, sizeof(str), file);
        tempChar = strtok(str, ",");
        processes[i]->name = (char) malloc(sizeof(char)*10);
        processes[i]->arrival = (int) malloc(sizeof(int));
        processes[i]->service = (int) malloc(sizeof(int));
        tempVal = (int*)strtok(str, ",");
        processes[i]->arrival = &tempVal;
        tempVal = (int*)strtok(str, ",");
        processes[i]->service = &tempVal;
        printf("Process name: %s\n Arr time: %d\n Ser Time: %d\n",
                processes[i]->name,
                processes[i]->arrival,
                processes[i]->service);
    }

    return 0;
}