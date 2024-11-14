#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 100

const char *valid_registers[] = {"AX", "BX", "CX", "DX"};
int num_valid_registers = 4;

int is_valid_register(const char *operand) {
    for (int i = 0; i < num_valid_registers; i++) {
        if (strcmp(operand, valid_registers[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_valid_immediate(const char *operand) {
    for (int i = 0; operand[i] != '\0'; i++) {
        if (!isdigit(operand[i])) {
            return 0;
        }
    }
    return 1;
}

void check_job_for_operand_errors(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        char opcode[10], dest[10], src[10];

        int num_operands = sscanf(line, "%s %[^,], %s", opcode, dest, src);

        if (num_operands == 3) {
            if (!is_valid_register(dest)) {
                printf("Interrupt: Invalid destination operand '%s' on line %d. Job halted.\n", dest, line_number);
                fclose(file);
                return;
            }
            if (!is_valid_register(src) && !is_valid_immediate(src)) {
                printf("Interrupt: Invalid source operand '%s' on line %d. Job halted.\n", src, line_number);
                fclose(file);
                return;
            }
            printf("Executing instruction: %s %s, %s\n", opcode, dest, src);
        } else {
            printf("Error: Invalid instruction format on line %d.\n", line_number);
        }
    }

    printf("Job completed without errors.\n");
    fclose(file);
}

int main() {
    char filename[50];
    printf("Enter the job file name: ");
    scanf("%s", filename);
    check_job_for_operand_errors(filename);
    return 0;
}

