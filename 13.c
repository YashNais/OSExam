
//Write a program to check whether given system is in safe state or not using Banker’s  Deadlock Avoidance algorithm.

#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void calculate_need(int need[MAX_PROCESSES][MAX_RESOURCES], int max[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES], int num_processes, int num_resources) {
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool is_safe_state(int processes[], int available[], int max[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES], int num_processes, int num_resources) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculate_need(need, max, allocation, num_processes, num_resources);
    
    bool finish[MAX_PROCESSES] = {false}; 
    int safe_sequence[MAX_PROCESSES];
    int work[MAX_RESOURCES];

    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < num_processes) {
        bool found = false;
        for (int p = 0; p < num_processes; p++) {
            if (finish[p] == false) { 
                int j;
                for (j = 0; j < num_resources; j++) {
                    if (need[p][j] > work[j])
                        break;
                }
                if (j == num_resources) { 
                    
                    for (int k = 0; k < num_resources; k++) {
                        work[k] += allocation[p][k]; 
                    }
                    safe_sequence[count++] = p;
                    finish[p] = true;
                    found = true;
                    break;  
                }
            }
        }
        if (found == false) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

 
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < num_processes; i++) {
        printf("%d ", safe_sequence[i]);
    }
    printf("\n");

    return true;
}

int main() {
    int num_processes, num_resources;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    int processes[MAX_PROCESSES];
    int available[MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the maximum matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available resources:\n");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }

    is_safe_state(processes, available, max, allocation, num_processes, num_resources);

    return 0;
}

