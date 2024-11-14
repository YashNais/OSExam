
//Write a program to simulate SSTF disk scheduling. Calculate total seek time.Print accepted input and output in tabular format

#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

int calculate_SSTF(int requests[], int num_requests, int initial_head) {
    int seek_time = 0;
    int visited[MAX_REQUESTS] = {0}; 
    int current_head = initial_head;

    for (int i = 0; i < num_requests; i++) {
        int min_seek_time = 10000; 
        int next_request_index = -1;

        for (int j = 0; j < num_requests; j++) {
            if (!visited[j]) { 
                int seek = abs(current_head - requests[j]);
                if (seek < min_seek_time) {
                    min_seek_time = seek;
                    next_request_index = j;
                }
            }
        }

        visited[next_request_index] = 1;
        seek_time += min_seek_time;
        current_head = requests[next_request_index];
    }

    return seek_time;
}

int main() {
    int num_requests, initial_head;
    
    printf("Enter the number of disk requests: ");
    scanf("%d", &num_requests);

    int requests[MAX_REQUESTS];

    printf("Enter the disk requests (separated by spaces): ");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &initial_head);

    int total_seek_time = 0;
    int visited[MAX_REQUESTS] = {0};
    int current_head = initial_head;

    printf("\nRequest No.\tRequested Track\tSeek Time\tCumulative Seek Time\n");

    for (int i = 0; i < num_requests; i++) {
        int min_seek_time = 10000;
        int next_request_index = -1;

        for (int j = 0; j < num_requests; j++) {
            if (!visited[j]) {
                int seek = abs(current_head - requests[j]);
                if (seek < min_seek_time) {
                    min_seek_time = seek;
                    next_request_index = j;
                }
            }
        }

        visited[next_request_index] = 1;
        total_seek_time += min_seek_time;

        printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, requests[next_request_index], min_seek_time, total_seek_time);
        current_head = requests[next_request_index];
    }

    return 0;
}

