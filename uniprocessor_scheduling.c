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
    struct process *processes[NUM_PROCESSES];


    fgets(str, sizeof(str), file); // Get header line

    // Add values into process array
    for(int i = 0; i < NUM_PROCESSES; i++)
    {
        struct process *newEntry;
        newEntry = (struct process*)malloc(sizeof(struct process));
        fgets(str, sizeof(str), file);
        tempChar = strtok(str, ",");
        strcpy(newEntry->name, tempChar);
        tempVal = (int*)strtok(str, ",");
        newEntry->arrival = &tempVal;
        tempVal = (int*)strtok(str, ",");
        newEntry->service = &tempVal;
        printf("Process name: %s\nArr time: %d\nSer Time: %d\n\n",
                newEntry->name,
                newEntry->arrival,
                newEntry->service);

    }

    return 0;
}
