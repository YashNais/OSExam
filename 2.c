/*Design menu driven application demonstrating use of different system calls.
1) Process related system call: fork, exit, wait
2) File realted system call: open, read, write, close, link, unlink, stat
3) Communication system call: pipe, fifo
4) Information related system call: sleep, alarm */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

void process_calls();
void file_calls();
void communication_calls();
void info_calls();

int main() {
    int choice;

    while (1) {
        printf("\nMenu Driven Application for System Calls\n");
        printf("1. Process Related System Calls\n");
        printf("2. File Related System Calls\n");
        printf("3. Communication Related System Calls\n");
        printf("4. Information Related System Calls\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                process_calls();
                break;
            case 2:
                file_calls();
                break;
            case 3:
                communication_calls();
                break;
            case 4:
                info_calls();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

void process_calls() {
    int pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
    } else if (pid == 0) {
        printf("Child process. PID: %d\n", getpid());
        exit(0);
    } else {
        wait(NULL);
        printf("Parent process. PID: %d\n", getpid());
    }
}

void file_calls() {
    char filename[100], buffer[100];
    int fd, bytes;
    struct stat fileStat;

    printf("Enter filename: ");
    scanf("%s", filename);

    fd = open(filename, O_CREAT | O_RDWR, 0666);
    if (fd < 0) {
        printf("Error opening file.\n");
        return;
    }

    printf("Writing to the file...\n");
    write(fd, "This is a test file.\n", 21);

    lseek(fd, 0, SEEK_SET);
    bytes = read(fd, buffer, sizeof(buffer));
    if (bytes < 0) {
        printf("Error reading file.\n");
        close(fd);
        return;
    }

    buffer[bytes] = '\0';
    printf("Content of %s:\n%s\n", filename, buffer);

    close(fd);

    printf("Creating a hard link to the file.\n");
    if (link(filename, "hardlink_file") == 0) {
        printf("Hard link created: hardlink_file\n");
    } else {
        printf("Error creating hard link.\n");
    }

    if (stat(filename, &fileStat) == 0) {
        printf("File size: %ld bytes\n", fileStat.st_size);
        printf("File inode: %ld\n", fileStat.st_ino);
        printf("File permissions: %o\n", fileStat.st_mode);
    } else {
        printf("Error getting file status.\n");
    }

    printf("Removing the hard link.\n");
    if (unlink("hardlink_file") == 0) {
        printf("Hard link removed: hardlink_file\n");
    } else {
        printf("Error removing hard link.\n");
    }
}

void communication_calls() {
    int fd[2];
    pid_t pid;
    char write_msg[] = "Hello, this is a message through pipe";
    char read_msg[100];
    char fifo_name[] = "my_fifo";

    if (pipe(fd) == -1) {
        printf("Pipe failed.\n");
        return;
    }

    pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        return;
    }

    if (pid > 0) {
        close(fd[0]);  
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]); 
        wait(NULL);
    } else {
        close(fd[1]); 
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Received message: %s\n", read_msg);
        close(fd[0]);
        exit(0);
    }

    if (mkfifo(fifo_name, 0666) == -1) {
        printf("Error creating FIFO.\n");
        return;
    }

    pid = fork();

    if (pid < 0) {
        printf("Fork failed.\n");
        return;
    }

    if (pid > 0) {
        fd[1] = open(fifo_name, O_WRONLY);
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]);
        wait(NULL); 
    } else {
        fd[0] = open(fifo_name, O_RDONLY);
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Received message from FIFO: %s\n", read_msg);
        close(fd[0]);
        exit(0);
    }

    unlink(fifo_name); 
}

void info_calls() {
    unsigned int seconds;

    printf("Enter time in seconds for sleep: ");
    scanf("%u", &seconds);

    printf("Sleeping for %u seconds...\n", seconds);
    sleep(seconds);
    printf("Woke up after %u seconds.\n", seconds);

    printf("Setting an alarm for 5 seconds.\n");
    alarm(5);
    pause();  
}
