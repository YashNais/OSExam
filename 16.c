
//Write a program to calculate the number of page faults for a reference string for the LRU page replacement algorithms: 

#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100


int LRU(int reference_string[], int n, int frames) {
    int page_faults = 0;
    int frames_array[MAX_FRAMES];
    int last_used[MAX_FRAMES];
    int time = 0; 

    
    for (int i = 0; i < frames; i++) {
        frames_array[i] = -1;
        last_used[i] = -1;
    }

    
    for (int i = 0; i < n; i++) {
        int page = reference_string[i];
        bool found = false;

        
        for (int j = 0; j < frames; j++) {
            if (frames_array[j] == page) {
                found = true;
                last_used[j] = time++; 
                break;
            }
        }

        
        if (!found) {
            page_faults++;
            int lru_index = 0;
            int min_time = last_used[0];

         
            for (int j = 1; j < frames; j++) {
                if (last_used[j] < min_time) {
                    min_time = last_used[j];
                    lru_index = j;
                }
            }

 
            frames_array[lru_index] = page;
            last_used[lru_index] = time++;  
        }
    }

    return page_faults;
}

int main() {
    int reference_string[MAX_PAGES];
    int n, frames;


    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &reference_string[i]);
    }

   
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

  
    int page_faults = LRU(reference_string, n, frames);


    printf("Total page faults: %d\n", page_faults);

    return 0;
}

