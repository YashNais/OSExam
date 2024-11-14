
//Write a program to compute the finish time, turnaround time and waiting time for the Priority (Preemptive and Non Preemptive)


#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;        
    int bt;       
    int art;      
    int prt;        
    int finishTime;  
};


void findWaitingTimePreemptive(struct Process proc[], int n, int wt[]) {
    int rt[n]; 
    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;

    int complete = 0, t = 0, minm = INT_MAX;
    int highestPriority = -1, finish_time;
    int check = 0;

   
    while (complete != n) {
        minm = INT_MAX;
        check = 0;

       
        for (int j = 0; j < n; j++) {
            if ((proc[j].art <= t) && (rt[j] > 0) && (proc[j].prt < minm)) {
                minm = proc[j].prt;
                highestPriority = j;
                check = 1;
            }
        }

        if (check == 0) {
            t++;
            continue;
        }

    
        rt[highestPriority]--;

     
        if (rt[highestPriority] == 0) {
            complete++;
            finish_time = t + 1;
            proc[highestPriority].finishTime = finish_time; 
            wt[highestPriority] = finish_time - proc[highestPriority].bt - proc[highestPriority].art;

            if (wt[highestPriority] < 0)
                wt[highestPriority] = 0;
        }

  
        t++;
    }
}


void findWaitingTimeNonPreemptive(struct Process proc[], int n, int wt[]) {
    int complete = 0, t = 0;
    int minm = INT_MAX, highestPriority = -1;
    int finish_time;

    
    int done[n];
    for (int i = 0; i < n; i++) {
        done[i] = 0;  
    }

    while (complete != n) {
        minm = INT_MAX;
        highestPriority = -1;

    
        for (int j = 0; j < n; j++) {
            if ((proc[j].art <= t) && !done[j] && proc[j].prt < minm) {
                minm = proc[j].prt;
                highestPriority = j;
            }
        }

        if (highestPriority == -1) {
           
            t++;
            continue;
        }

       
        done[highestPriority] = 1;

     
        t += proc[highestPriority].bt;
        proc[highestPriority].finishTime = t;
        wt[highestPriority] = proc[highestPriority].finishTime - proc[highestPriority].bt - proc[highestPriority].art;

        if (wt[highestPriority] < 0)
            wt[highestPriority] = 0;

        complete++;
    }
}


void findTurnAroundTime(struct Process proc[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];
}


void displayResults(struct Process proc[], int n, int wt[], int tat[]) {
    printf("\nProcess\tArrival\tBurst\tPriority\tFinish\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("  %d\t  %d\t  %d\t  %d\t  %d\t  %d\t  %d\n",
               proc[i].pid, proc[i].art, proc[i].bt, proc[i].prt,
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
        printf("Enter arrival time, burst time, and priority for Process %d: ", proc[i].pid);
        scanf("%d %d %d", &proc[i].art, &proc[i].bt, &proc[i].prt);
    }

    
    printf("\nChoose the Scheduling type:\n");
    printf("1. Preemptive Priority\n");
    printf("2. Non-Preemptive Priority\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    findTimes(proc, n, choice);

    return 0;
}

