
//Write a program to read and copy the contents of file character by character, line by line.

#include <stdio.h>
#include <stdlib.h>

void copy_char_by_char(FILE *source, FILE *destination) {
    char ch;
    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, destination);
    }
    printf("File copied character by character successfully.\n");
}

void copy_line_by_line(FILE *source, FILE *destination) {
    char buffer[1024]; 
    while (fgets(buffer, sizeof(buffer), source) != NULL) {
        fputs(buffer, destination);
    }
    printf("File copied line by line successfully.\n");
}

int main() {
    char source_file[100], dest_file[100];
    int choice;

    printf("Enter the source file name: ");
    scanf("%s", source_file);
    printf("Enter the destination file name: ");
    scanf("%s", dest_file);

    FILE *source = fopen(source_file, "r");
    if (source == NULL) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }

    FILE *destination = fopen(dest_file, "w");
    if (destination == NULL) {
        perror("Error opening destination file");
        fclose(source);
        return EXIT_FAILURE;
    }


    printf("Choose copy method:\n1. Copy character by character\n2. Copy line by line\n");
    scanf("%d", &choice);


    if (choice == 1) {
        copy_char_by_char(source, destination);
    } else if (choice == 2) {
        copy_line_by_line(source, destination);
    } else {
        printf("Invalid choice.\n");
    }


    fclose(source);
    fclose(destination);

    return EXIT_SUCCESS;
}


/*

//Write a program to read and copy the contents of file character by character, line by line.

#include <stdio.h>
#include <stdlib.h>

void copy_char_by_char(FILE *source) {
    char ch;
    while ((ch = fgetc(source)) != EOF) {
        putchar(ch);
    }
    printf("File copied character by character successfully.\n");
}

void copy_line_by_line(FILE *source) {
    char buffer[1024]; 
    while (fgets(buffer, sizeof(buffer), source) != NULL) {
        printf("%s", buffer);
    }
    printf("File copied line by line successfully.\n");
}

int main() {
    char source_file[100];
    int choice;

    printf("Enter the source file name: ");
    scanf("%s", source_file);

    FILE *source = fopen(source_file, "r");
    if (source == NULL) {
        perror("Error opening source file");
        return EXIT_FAILURE;
    }


    printf("Choose copy method:\n1. Copy character by character\n2. Copy line by line\n");
    scanf("%d", &choice);


    if (choice == 1) {
        copy_char_by_char(source);
    } else if (choice == 2) {
        copy_line_by_line(source);
    } else {
        printf("Invalid choice.\n");
    }


    fclose(source);

    return EXIT_SUCCESS;
}
*/
