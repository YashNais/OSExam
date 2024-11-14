#include <stdio.h>

void main() {
    int i, j, NOP, sum = 0, count = 0, quantum;
    int at[10], bt[10], temp[10], finish_time[10], turnaround_time[10], waiting_time[10];
    int wt = 0, tat = 0;


    printf("Enter total number of processes: ");
    scanf("%d", &NOP);


    for (i = 0; i < NOP; i++) {
        printf("\nEnter the Arrival and Burst time of Process[%d]:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &at[i]);
        printf("Burst time: ");
        scanf("%d", &bt[i]);
        temp[i] = bt[i];  
    }

    
    printf("Enter the Time Quantum for the processes: ");
    scanf("%d", &quantum);

    
    printf("\nProcess No\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");

    int y = NOP;
    for (sum = 0, i = 0; y > 0;) {
        if (temp[i] <= quantum && temp[i] > 0) {
            sum += temp[i];
            finish_time[i] = sum;
            temp[i] = 0;
            count = 1;
        } else if (temp[i] > 0) {
            temp[i] -= quantum;
            sum += quantum;
        }
        
      
        if (temp[i] == 0 && count == 1) {
            y--; 
            turnaround_time[i] = finish_time[i] - at[i];
            waiting_time[i] = turnaround_time[i] - bt[i];

            
            printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], finish_time[i], turnaround_time[i], waiting_time[i]);

            wt += waiting_time[i];
            tat += turnaround_time[i];
            count = 0;
        }

        
        if (i == NOP - 1) {
            i = 0;
        } else if (at[i + 1] <= sum) {
            i++;
        } else {
            i = 0;
        }
    }

}

