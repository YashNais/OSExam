#include <stdio.h>
#include <string.h>

// Define the maximum number of instructions and the maximum length of an instruction
#define MAX_INSTRUCTIONS 100
#define MAX_OPCODE_LENGTH 10

// List of valid opcodes
const char *valid_opcodes[] = {"MOV", "ADD", "SUB", "MUL", "DIV", "HLT"};
#define NUM_VALID_OPCODES 6

// Function to check if an opcode is valid
int is_valid_opcode(const char *opcode) {
    for (int i = 0; i < NUM_VALID_OPCODES; i++) {
        if (strcmp(opcode, valid_opcodes[i]) == 0) {
            return 1;  // Valid opcode
        }
    }
    return 0;  // Invalid opcode
}

// Function to simulate loading and checking the job
void load_and_check_job(FILE *job_file) {
    char instruction[MAX_OPCODE_LENGTH + 50];  // to store each instruction
    char opcode[MAX_OPCODE_LENGTH];
    char operand[50];
    int line_num = 0;

    // Process each line in the job file
    while (fgets(instruction, sizeof(instruction), job_file) != NULL) {
        line_num++;
        
        // Parse the instruction (assuming format: OPCODE OPERAND)
        if (sscanf(instruction, "%s %s", opcode, operand) < 2) {
            printf("Error on line %d: Invalid instruction format!\n", line_num);
            continue;  // Skip invalid instructions
        }

        // Check if the opcode is valid
        if (!is_valid_opcode(opcode)) {
            printf("Interrupt: Invalid opcode '%s' found at line %d! Job halted.\n", opcode, line_num);
            return;  // Raise interrupt and stop further execution
        }

        // Print the valid instruction (simulating execution)
        printf("Executing instruction: %s %s\n", opcode, operand);
    }

    printf("Job completed without errors.\n");
}

int main() {
    char filename[50];

    // Ask for the input job file
    printf("Enter the job file name: ");
    scanf("%s", filename);

    // Open the file for reading
    FILE *job_file = fopen(filename, "r");
    if (job_file == NULL) {
        printf("Error opening file %s\n", filename);
        return 1;  // Exit if the file can't be opened
    }

    // Load and check the job file for opcode errors
    load_and_check_job(job_file);

    // Close the job file
    fclose(job_file);

    return 0;
}

