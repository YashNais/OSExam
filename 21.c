
//Write a program to simulate C-SCAN disk scheduling. Calculate total seek time.Print accepted input and output in tabular format

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

void cscan_disk_scheduling(int requests[], int n, int head, int disk_size) {
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
    if (right_count > 0 && (left_count == 0 || (right[0] - head) < (head - left[left_count - 1]))) {
        direction = 'R'; 
    } else {
        direction = 'L';  
    }

    printf("\nAutomatically determined direction: %c\n", direction);
    printf("\nRequest No.\tRequested Track\tSeek Time\tCumulative Seek Time\n");

    int cumulative_seek_time = 0;
    int request_no = 1;

    if (direction == 'R') {

        for (int i = 0; i < right_count; i++) {
            seek_time = abs(right[i] - head);
            total_seek_time += seek_time;
            cumulative_seek_time += seek_time;
            printf("%d\t\t%d\t\t%d\t\t%d\n", request_no++, right[i], seek_time, cumulative_seek_time);
            head = right[i];
        }

        if (head < disk_size) {
            seek_time = abs(disk_size - head);
            total_seek_time += seek_time;
            cumulative_seek_time += seek_time;
            printf("%d\t\t%d\t\t%d\t\t%d\n", request_no++, disk_size, seek_time, cumulative_seek_time);
            head = disk_size;
        }

        seek_time = abs(disk_size - 0);
        total_seek_time += seek_time;
        cumulative_seek_time += seek_time;
        printf("%d\t\t%d\t\t%d\t\t%d\n", request_no++, 0, seek_time, cumulative_seek_time);
        head = 0;

        for (int i = 0; i < left_count; i++) {
            seek_time = abs(left[i] - head);
            total_seek_time += seek_time;
            cumulative_seek_time += seek_time;
            printf("%d\t\t%d\t\t%d\t\t%d\n", request_no++, left[i], seek_time, cumulative_seek_time);
            head = left[i];
        }
    } else {  

        for (int i = left_count - 1; i >= 0; i--) {
            seek_time = abs(left[i] - head);
            total_seek_time += seek_time;
            cumulative_seek_time += seek_time;
            printf("%d\t\t%d\t\t%d\t\t%d\n", request_no++, left[i], seek_time, cumulative_seek_time);
            head = left[i];
        }

        if (head > 0) {
            seek_time = abs(head);
            total_seek_time += seek_time;
            cumulative_seek_time += seek_time;
            printf("%d\t\t%d\t\t%d\t\t%d\n", request_no++, 0, seek_time, cumulative_seek_time);
            head = 0;
        }

        seek_time = abs(disk_size - 0);
        total_seek_time += seek_time;
        cumulative_seek_time += seek_time;
        printf("%d\t\t%d\t\t%d\t\t%d\n", request_no++, disk_size, seek_time, cumulative_seek_time);
        head = disk_size;

        for (int i = 0; i < right_count; i++) {
            seek_time = abs(right[i] - head);
            total_seek_time += seek_time;
            cumulative_seek_time += seek_time;
            printf("%d\t\t%d\t\t%d\t\t%d\n", request_no++, right[i], seek_time, cumulative_seek_time);
            head = right[i];
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

    cscan_disk_scheduling(requests, n, head, disk_size);

    return 0;
}

