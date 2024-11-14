
//Write a program to compute the finish time, turnaround time and waiting time for the First come First serve

#include <stdio.h>

int main() {
    int n, i;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    int arrival_time[n], burst_time[n], finish_time[n], turnaround_time[n], waiting_time[n];
    
    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
    }

    int current_time = 0;
    for (i = 0; i < n; i++) {

        if (current_time < arrival_time[i]) {
            current_time = arrival_time[i];
        }
        
        finish_time[i] = current_time + burst_time[i];
        
        current_time = finish_time[i];
        
        turnaround_time[i] = finish_time[i] - arrival_time[i];
        waiting_time[i] = turnaround_time[i] - burst_time[i];
    }

    printf("\nProcess\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival_time[i], burst_time[i], finish_time[i], turnaround_time[i], waiting_time[i]);
    }

    return 0;
}

