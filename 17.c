
//Write a program to calculate the number of page faults for a reference string for the Optimal page replacement algorithms: 

#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100


int findOptimal(int reference_string[], int frames_array[], int current_page, int n, int frames) {
    int farthest = -1;
    int replace_index = -1;


    for (int i = 0; i < frames; i++) {
        int j;

        for (j = current_page; j < n; j++) {
            if (frames_array[i] == reference_string[j]) {
                break;
            }
        }


        if (j == n) {
            return i;
        }


        if (j > farthest) {
            farthest = j;
            replace_index = i;
        }
    }

    return replace_index;
}

int optimalPageReplacement(int reference_string[], int n, int frames) {
    int page_faults = 0;
    int frames_array[MAX_FRAMES];

    for (int i = 0; i < frames; i++) {
        frames_array[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = reference_string[i];
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (frames_array[j] == page) {
                found = 1;
                break;
            }
        }


        if (!found) {
            page_faults++;
            int replace_index = -1;

            for (int j = 0; j < frames; j++) {
                if (frames_array[j] == -1) {
                    replace_index = j;
                    break;
                }
            }


            if (replace_index == -1) {
                replace_index = findOptimal(reference_string, frames_array, i + 1, n, frames);
            }

            frames_array[replace_index] = page;
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


    int page_faults = optimalPageReplacement(reference_string, n, frames);

    printf("Total page faults: %d\n", page_faults);

    return 0;
}

