
//Write a program to calculate the number of page faults for a reference string for the FIFO page replacement algorithms

#include <stdio.h>

int main() {
    int num_pages, num_frames;
    printf("Enter the number of pages in the reference string: ");
    scanf("%d", &num_pages);

    int reference_string[num_pages];
    printf("Enter the reference string:\n");
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &reference_string[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);

    int frames[num_frames]; 
    int page_faults = 0;
    int next_to_replace = 0; 

    
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }

    
    for (int i = 0; i < num_pages; i++) {
        int page = reference_string[i];
        int found = 0;

        
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        
        if (!found) {
            frames[next_to_replace] = page;
            next_to_replace = (next_to_replace + 1) % num_frames; 
            page_faults++;
        }
    }

    printf("Total number of page faults: %d\n", page_faults);

    return 0;
}

