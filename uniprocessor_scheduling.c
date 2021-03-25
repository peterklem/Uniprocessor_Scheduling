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
        struct process *newEntry;
        newEntry = (struct process*)malloc(sizeof(struct process));
        fgets(str, sizeof(str), file);
        tempChar = strtok(str, ",");
        strcpy(newEntry->name, tempChar);
        tempChar = strtok(NULL, ",");
        newEntry->arrival = atoi(tempChar);
        tempChar = strtok(NULL, ",");
        newEntry->service = atoi(tempChar);
        printf("Process name: %s\nArr time: %d\nSer Time: %d\n\n",
                newEntry->name,
                newEntry->arrival,
                newEntry->service);
        processes[i] = newEntry;

    }

    return 0;
}
