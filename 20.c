
//Write a program to simulate SCAN disk scheduling. Calculate total seek time.Print accepted input and output in tabular format

#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void sort(int requests[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }
}

void scan_disk_scheduling(int requests[], int n, int head, int disk_size) {
    int total_seek_time = 0, seek_time;
    int left[MAX_REQUESTS], right[MAX_REQUESTS];
    int left_count = 0, right_count = 0;


    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[left_count++] = requests[i];
        else
            right[right_count++] = requests[i];
    }


    sort(left, left_count);
    sort(right, right_count);


    char direction;
    if (left_count == 0) 
    {
        direction = 'R';
    } 
    else if (right_count == 0) 
    {
        direction = 'L';  
    } 
    else 
    {
     
        if (abs(head - left[left_count - 1]) < abs(head - right[0])) {
            direction = 'L';  
        } else {
            direction = 'R'; 
        }
    }

    printf("Direction: %c\n", direction);

    printf("\nRequest No.\tRequested Track\tSeek Time\tCumulative Seek Time\n");
    int cumulative_seek_time = 0;


    if (direction == 'L' || direction == 'l') {

        if (left_count > 0) {

            seek_time = head;
            total_seek_time += seek_time;
            cumulative_seek_time += seek_time;
            printf("%d\t\t0\t\t%d\t\t%d\n", 1, seek_time, cumulative_seek_time);

            for (int i = left_count - 1; i >= 0; i--) {
                seek_time = abs(left[i] - head);
                total_seek_time += seek_time;
                cumulative_seek_time += seek_time;
                printf("%d\t\t%d\t\t%d\t\t%d\n", left_count - i + 1, left[i], seek_time, cumulative_seek_time);
                head = left[i];
            }
        }

        if (right_count > 0) {

            for (int i = 0; i < right_count; i++) {
                seek_time = abs(right[i] - head);
                total_seek_time += seek_time;
                cumulative_seek_time += seek_time;
                printf("%d\t\t%d\t\t%d\t\t%d\n", left_count + i + 2, right[i], seek_time, cumulative_seek_time);
                head = right[i];
            }
        }
    } else if (direction == 'R' || direction == 'r') {

        if (right_count > 0) {

            for (int i = 0; i < right_count; i++) {
                seek_time = abs(right[i] - head);
                total_seek_time += seek_time;
                cumulative_seek_time += seek_time;
                printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, right[i], seek_time, cumulative_seek_time);
                head = right[i];
            }
        }

        if (left_count > 0) {

            for (int i = left_count - 1; i >= 0; i--) {
                seek_time = abs(left[i] - head);
                total_seek_time += seek_time;
                cumulative_seek_time += seek_time;
                printf("%d\t\t%d\t\t%d\t\t%d\n", right_count + left_count - i + 1, left[i], seek_time, cumulative_seek_time);
                head = left[i];
            }
        }
    }

    printf("\nTotal seek time: %d\n", total_seek_time);
}

int main() {
    int requests[MAX_REQUESTS], n, head, disk_size;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk requests (separated by spaces): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    printf("Enter the total disk size (maximum track number): ");
    scanf("%d", &disk_size);

    scan_disk_scheduling(requests, n, head, disk_size);

    return 0;
}

