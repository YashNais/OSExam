
//Write a program to load ALP program from input file to main memory.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMORY_SIZE 100  


void load_ALP_to_memory(const char *file_name) {
    FILE *file;
    char line[256]; 
    char *memory[MAX_MEMORY_SIZE]; 
    int memory_address = 0;  

  
    file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error: Could not open the file %s\n", file_name);
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
     
        line[strcspn(line, "\n")] = '\0';


        if (memory_address < MAX_MEMORY_SIZE) {
 
            memory[memory_address] = (char *)malloc(strlen(line) + 1);
            if (memory[memory_address] == NULL) {
                printf("Error: Memory allocation failed\n");
                fclose(file);
                return;
            }
            strcpy(memory[memory_address], line);
            printf("Loading Instruction: %s into memory at address %d\n", memory[memory_address], memory_address);
            memory_address++;
        } else {
            printf("Error: Memory overflow, too many instructions.\n");
            break;
        }
    }

    fclose(file);

    printf("\n--- Main Memory After Loading ALP ---\n");
    for (int i = 0; i < memory_address; i++) {
        printf("Memory[%d]: %s\n", i, memory[i]);
    }

    for (int i = 0; i < memory_address; i++) {
        free(memory[i]);
    }
}

int main() {
    char file_name[100];

    printf("Enter the ALP program file name: ");
    scanf("%s", file_name);

    load_ALP_to_memory(file_name);

    return 0;
}

