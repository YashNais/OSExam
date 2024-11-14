
//Write a program to simulate FCFS disk scheduling. Calculate total seek time.Print accepted input and output in tabular format

#include <stdio.h>
#include <stdlib.h>

void fcfsDiskScheduling(int requests[], int num_requests, int initial_position) {
    int total_seek_time = 0;
    int current_position = initial_position;
    
    printf("Request No.\tRequested Track\tSeek Time\tCumulative Seek Time\n");

    for (int i = 0; i < num_requests; i++) {
        int seek_time = abs(requests[i] - current_position);
        total_seek_time += seek_time;

        printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, requests[i], seek_time, total_seek_time);
        
        current_position = requests[i];
    }

    printf("\nTotal Seek Time: %d\n", total_seek_time);
}

int main() {
    int num_requests, initial_position;

    printf("Enter the number of disk requests: ");
    scanf("%d", &num_requests);

    int requests[num_requests];

    printf("Enter the disk requests:\n");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial position of the disk arm: ");
    scanf("%d", &initial_position);

    fcfsDiskScheduling(requests, num_requests, initial_position);

    return 0;
}

