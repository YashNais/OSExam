
//Write a program  for following 1)  zombie process 2),orphan processes 3)sum of even numbers of an array in parent and odd numbers of an array in child process

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) { 
        printf("Parent process PID: %d\n", getpid());
        printf("Parent is sleeping for 5 seconds...\n");
        sleep(5);  
        printf("Parent process exits.\n");
    } else if (pid == 0) {  
        printf("Child process PID: %d\n", getpid());
        printf("Child process is done.\n");
        exit(0);  
    } else {
        perror("Fork failed");
        return 1;
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {  
        printf("Parent process PID: %d\n", getpid());
        printf("Parent process is terminating, making the child an orphan.\n");
        exit(0); 
    } 
    else if (pid == 0) {  
        sleep(5);  
        printf("Orphan child process PID: %d, New Parent PID: %d\n", getpid(), getppid());
    } 
    else {
        perror("Fork failed");
        return 1;
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int even_sum = 0, odd_sum = 0;
    pid_t pid = fork();

    if (pid > 0) {  
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 == 0) {
                even_sum += arr[i];
            }
        }
        printf("Parent process PID: %d\n", getpid());
        printf("Sum of even numbers: %d\n", even_sum);
        wait(NULL); 
    } else if (pid == 0) { 
        for (int i = 0; i < n; i++) {
            if (arr[i] % 2 != 0) {
                odd_sum += arr[i];
            }
        }
        printf("Child process PID: %d\n", getpid());
        printf("Sum of odd numbers: %d\n", odd_sum);
        exit(0);
    } else {
        perror("Fork failed");
        return 1;
    }

    return 0;
}


