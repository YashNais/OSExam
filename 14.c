
//Write a program for Deadlock detection algorithm

#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void calculate_need(int need[MAX_PROCESSES][MAX_RESOURCES], int request[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES], int num_processes, int num_resources) {
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            need[i][j] = request[i][j] - allocation[i][j];
        }
    }
}

bool is_safe_state(int processes[], int available[], int request[MAX_PROCESSES][MAX_RESOURCES], int allocation[MAX_PROCESSES][MAX_RESOURCES], int num_processes, int num_resources) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculate_need(need, request, allocation, num_processes, num_resources);
    
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];

    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    for (int count = 0; count < num_processes; count++) {
        int p = processes[count];

        if (!finish[p]) {
            int j;
            for (j = 0; j < num_resources; j++) {
                if (need[p][j] > work[j])
                    break;
            }
            if (j == num_resources) {
                for (int k = 0; k < num_resources; k++) {
                    work[k] += allocation[p][k];
                }
                finish[p] = true;
            } else {
                printf("System is in deadlock for the given process order.\n");
                return false;
            }
        }
    }

    printf("System is not in deadlock for the given process order.\n");
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
    int request[MAX_PROCESSES][MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the request matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("Enter the available resources:\n");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the process order (e.g., for P0, P1, P2 enter 0 1 2):\n");
    for (int i = 0; i < num_processes; i++) {
        scanf("%d", &processes[i]);
    }

    is_safe_state(processes, available, request, allocation, num_processes, num_resources);

    return 0;
}

