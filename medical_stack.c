#include <stdio.h>
#include <string.h>

#define MAX 10
#define SIZE 100

char stack[MAX][SIZE];
int top = -1;

/* Open New Report (Push) */
void openReport(char report[]) {
    if (top == MAX - 1) {
        printf("\nHistory Full! Cannot open more reports.\n");
        return;
    }

    top++;
    strcpy(stack[top], report);

    printf("\nOpened Report: %s\n", report);
}

/* Go Back (Pop) */
void goBack() {
    if (top == -1) {
        printf("\nNo Previous Report Available.\n");
        return;
    }

    printf("\nClosed Report: %s\n", stack[top]);
    top--;
}

/* Show Current Report */
void currentReport() {
    if (top == -1) {
        printf("\nNo Report Opened.\n");
        return;
    }

    printf("\nCurrent Report: %s\n", stack[top]);
}

/* Display History */
void displayHistory() {
    if (top == -1) {
        printf("\nNo History Available.\n");
        return;
    }

    printf("\nOpened Report History:\n");
    for (int i = top; i >= 0; i--) {
        printf("%d. %s\n", i + 1, stack[i]);
    }
}

/* Main Function */
int main() {
    int choice;
    char report[SIZE];

    while (1) {
        printf("\n--- Medical Report Navigation System ---\n");
        printf("1. Open New Report\n");
        printf("2. Go Back\n");
        printf("3. View Current Report\n");
        printf("4. View History\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter Report Name: ");
                fgets(report, SIZE, stdin);
                report[strcspn(report, "\n")] = '\0';
                openReport(report);
                break;

            case 2:
                goBack();
                break;

            case 3:
                currentReport();
                break;

            case 4:
                displayHistory();
                break;

            case 5:
                printf("\nExiting System. Goodbye Doctor! 👩‍⚕️👨‍⚕️\n");
                return 0;

            default:
                printf("\nInvalid Choice!\n");
        }
    }
}
