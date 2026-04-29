#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

char disk[MAX][20];

/* -------- Initialize Disk -------- */
void initializeDisk() {
    for (int i = 0; i < MAX; i++)
        strcpy(disk[i], "Free");
}

/* -------- Display Disk -------- */
void displayDisk() {
    printf("\nDisk Block Status:\n");
    for (int i = 0; i < MAX; i++) {
        printf("Block %-2d : %s\n", i, disk[i]);
    }
}

/* -------- Sequential Allocation -------- */
void sequentialAllocation() {
    char fileName[20];
    int start, length, flag = 1;

    printf("\n--- Sequential Allocation ---\n");

    printf("Enter file name: ");
    scanf("%19s", fileName);

    printf("Enter starting block: ");
    scanf("%d", &start);

    printf("Enter file length: ");
    scanf("%d", &length);

    // Validation
    if (start < 0 || length <= 0 || start + length > MAX) {
        printf("Invalid input.\n");
        return;
    }

    for (int i = start; i < start + length; i++) {
        if (strcmp(disk[i], "Free") != 0) {
            flag = 0;
            break;
        }
    }

    if (flag) {
        for (int i = start; i < start + length; i++)
            strcpy(disk[i], fileName);

        printf("File \"%s\" allocated successfully.\n", fileName);

        printf("Allocated blocks: ");
        for (int i = start; i < start + length; i++)
            printf("%d ", i);
        printf("\n");

    } else {
        printf("Allocation failed. Blocks unavailable.\n");
    }
}

/* -------- Linked Allocation -------- */
void linkedAllocation() {
    char fileName[20];
    int length, blocks[MAX], flag = 1;

    printf("\n--- Linked Allocation ---\n");

    printf("Enter file name: ");
    scanf("%19s", fileName);

    printf("Enter number of blocks: ");
    scanf("%d", &length);

    if (length <= 0 || length > MAX) {
        printf("Invalid length.\n");
        return;
    }

    printf("Enter block numbers: ");
    for (int i = 0; i < length; i++) {
        scanf("%d", &blocks[i]);

        if (blocks[i] < 0 || blocks[i] >= MAX ||
            strcmp(disk[blocks[i]], "Free") != 0) {
            flag = 0;
        }
    }

    if (flag) {
        for (int i = 0; i < length; i++)
            strcpy(disk[blocks[i]], fileName);

        printf("File \"%s\" allocated successfully.\n", fileName);

        printf("Linked blocks: ");
        for (int i = 0; i < length; i++) {
            printf("%d", blocks[i]);
            if (i != length - 1)
                printf(" -> ");
        }
        printf(" -> NULL\n");

    } else {
        printf("Allocation failed. One or more blocks unavailable.\n");
    }
}

/* -------- Indexed Allocation -------- */
void indexedAllocation() {
    char fileName[20];
    int indexBlock, length, blocks[MAX], flag = 1;

    printf("\n--- Indexed Allocation ---\n");

    printf("Enter file name: ");
    scanf("%19s", fileName);

    printf("Enter index block: ");
    scanf("%d", &indexBlock);

    if (indexBlock < 0 || indexBlock >= MAX ||
        strcmp(disk[indexBlock], "Free") != 0) {
        printf("Index block unavailable.\n");
        return;
    }

    printf("Enter number of blocks: ");
    scanf("%d", &length);

    if (length <= 0 || length > MAX) {
        printf("Invalid length.\n");
        return;
    }

    printf("Enter block numbers: ");
    for (int i = 0; i < length; i++) {
        scanf("%d", &blocks[i]);

        if (blocks[i] < 0 || blocks[i] >= MAX ||
            strcmp(disk[blocks[i]], "Free") != 0) {
            flag = 0;
        }
    }

    if (flag) {
        strcpy(disk[indexBlock], "INDEX");

        for (int i = 0; i < length; i++)
            strcpy(disk[blocks[i]], fileName);

        printf("File \"%s\" allocated successfully.\n", fileName);

        printf("Index block %d contains: ", indexBlock);
        for (int i = 0; i < length; i++)
            printf("%d ", blocks[i]);
        printf("\n");

    } else {
        printf("Allocation failed. Blocks unavailable.\n");
    }
}

/* -------- Main -------- */
int main() {
    int choice;
    initializeDisk();

    while (1) {
        printf("\n===== File Allocation Method Simulation =====\n");
        printf("1. Sequential Allocation\n");
        printf("2. Linked Allocation\n");
        printf("3. Indexed Allocation\n");
        printf("4. Display Disk Status\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sequentialAllocation();
                break;
            case 2:
                linkedAllocation();
                break;
            case 3:
                indexedAllocation();
                break;
            case 4:
                displayDisk();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
}