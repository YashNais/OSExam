
//Write a program to compute the finish time, turnaround time and waiting time for the Shortest Job First (Preemptive and Non Preemptive) 


#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;         
    int bt;        
    int art;         
    int finishTime;  
};

void findWaitingTimePreemptive(struct Process proc[], int n, int wt[]) {
    int rt[n];  
    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = -1, finish_time;
    int check = 0;

    while (complete != n) {
        minm = INT_MAX;
        check = 0;

        for (int j = 0; j < n; j++) {
            if ((proc[j].art <= t) && (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = 1;
            }
        }

        if (check == 0) {
            t++;
            continue;
        }

    
        rt[shortest]--;

    
        if (rt[shortest] == 0) {
            complete++;
            finish_time = t + 1;
            proc[shortest].finishTime = finish_time; 
            wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].art;

            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }

    
        t++;
    }
}


void findWaitingTimeNonPreemptive(struct Process proc[], int n, int wt[]) {
    int complete = 0, t = 0;
    int minm = INT_MAX, shortest = -1;
    int finish_time;

 
    int done[n];
    for (int i = 0; i < n; i++) {
        done[i] = 0;  
    }

    while (complete != n) {
        minm = INT_MAX;
        shortest = -1;

        for (int j = 0; j < n; j++) {
            if ((proc[j].art <= t) && !done[j] && proc[j].bt < minm) {
                minm = proc[j].bt;
                shortest = j;
            }
        }

        if (shortest == -1) {
            t++;
            continue;
        }

    
        done[shortest] = 1;

  
        t += proc[shortest].bt;
        proc[shortest].finishTime = t;
        wt[shortest] = proc[shortest].finishTime - proc[shortest].bt - proc[shortest].art;

        if (wt[shortest] < 0)
            wt[shortest] = 0;

        complete++;
    }
}

void findTurnAroundTime(struct Process proc[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}


void displayResults(struct Process proc[], int n, int wt[], int tat[]) {
    printf("\nProcess\tArrival\tBurst\tFinish\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("  %d\t  %d\t  %d\t  %d\t  %d\t  %d\n",
               proc[i].pid, proc[i].art, proc[i].bt,
               proc[i].finishTime, wt[i], tat[i]);
    }
}

void findTimes(struct Process proc[], int n, int choice) {
    int wt[n], tat[n];

    if (choice == 1) {
     
        findWaitingTimePreemptive(proc, n, wt);
    } else {
     
        findWaitingTimeNonPreemptive(proc, n, wt);
    }

    findTurnAroundTime(proc, n, wt, tat);
    displayResults(proc, n, wt, tat);
}


int main() {
    int n, choice;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time and burst time for Process %d: ", proc[i].pid);
        scanf("%d %d", &proc[i].art, &proc[i].bt);
    }


    printf("\nChoose the Scheduling type:\n");
    printf("1. Preemptive SJF\n");
    printf("2. Non-Preemptive SJF\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    findTimes(proc, n, choice);

    return 0;
}

