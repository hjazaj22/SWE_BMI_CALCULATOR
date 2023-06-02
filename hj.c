#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// ANSI escape sequences for text color
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_PINK    "\x1b[35m"
#define ANSI_COLOR_WHITE   "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_BACKGROUND_WHITE "\x1b[47m"

// Structure to store BMI calculation history
typedef struct {
    float height;
    float weight;
    float bmi;
    char classification[20];
} BMIRecord;

// Function to calculate BMI
float calculateBMI(float height, float weight, int isMetric) {
    if (isMetric) {
        // BMI calculation for metric units (height in meters, weight in kilograms)
        return weight / (height * height);
    } else {
        // BMI calculation for imperial units (height in inches, weight in pounds)
        return (weight * 703) / (height * height);
    }
}

// Function to classify BMI
void classifyBMI(float bmi, char *classification) {
    if (bmi < 18.5) {
        sprintf(classification, "Underweight");
    } else if (bmi < 25.0) {
        sprintf(classification, "Normal weight");
    } else if (bmi < 30.0) {
        sprintf(classification, "Overweight");
    } else {
        sprintf(classification, "Obese");
    }
}

// Function to display BMI calculation history
void displayHistory(BMIRecord *history, int count) {
    printf(ANSI_COLOR_BLUE "\nBMI Calculation History:\n");
    printf("------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("User %d:\n", i + 1);
        printf("Height: %.2f\n", history[i].height);
        printf("Weight: %.2f\n", history[i].weight);
        printf("BMI: %.2f\n", history[i].bmi);
        printf("Classification: %s\n", history[i].classification);
        printf("------------------------------\n");
    }
    printf(ANSI_COLOR_RESET);
}

// Function to display colorful header
void displayHeader() {
    system("clear"); // Clear the console (for UNIX-like systems)
    printf("\n");

    printf(ANSI_BACKGROUND_WHITE ANSI_COLOR_BLUE);
    printf("******************************\n");
    printf("*                            *\n");
    printf("*   Welcome to the BMI       *\n");
    printf("*        Calculator          *\n");
    printf("*                            *\n");
    printf("*   Let's calculate your BMI *\n");
    printf("*                            *\n");
    printf("******************************\n");
    printf("\n");
    printf(ANSI_COLOR_RESET);
   
    printf("\n");
}

// Function to play sound effect
void playSoundEffect() {
    printf("\a"); // ASCII bell character to produce a sound
}

// Function to display animated progress bar
void displayProgressBar() {
    printf("Calculating BMI ");
    for (int i = 0; i < 10; i++) {
        printf(ANSI_COLOR_BLUE "▓" ANSI_COLOR_RESET);
        fflush(stdout);
        usleep(200000); // Sleep for 200 milliseconds
    }
    printf(ANSI_COLOR_BLUE " 100%%\n" ANSI_COLOR_RESET);
}

// Function to personalize messages
void personalizeMessage(const char *name) {
    printf(ANSI_COLOR_PINK "Hello, %s!\n", name);
    printf("Let's calculate your BMI.\n");
    printf("\n");
    printf(ANSI_COLOR_RESET);
}

int main() {
    BMIRecord history[10]; // Assuming maximum of 10 BMI records
    int recordCount = 0;

    int isMetric = 0; // Flag to check if metric units are used

    char name[50]; // Variable to store the user's name
    printf(ANSI_COLOR_BLUE "Enter your name: ");
    scanf("%s", name);
    printf(ANSI_COLOR_RESET);

    displayHeader();
    personalizeMessage(name);

    while (1) {
        int choice;
        printf(ANSI_COLOR_BLUE "Options:\n");
        printf("1. Calculate BMI\n");
        printf("2. View History\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf(ANSI_COLOR_RESET);

        switch (choice) {
            case 1: {
                float height, weight;

                printf(ANSI_COLOR_PINK "\nUnit Conversion:\n");
                printf("1. Metric (height in meters, weight in kilograms)\n");
                printf("2. Imperial (height in inches, weight in pounds)\n");
                printf("Enter your choice: ");
                scanf("%d", &isMetric);

                printf("\nEnter your height: ");
                scanf("%f", &height);

                printf("Enter your weight: ");
                scanf("%f", &weight);

                if (height <= 0 || weight <= 0) {
                    printf("\nError: Invalid input!\n");
                    break;
                }

                displayProgressBar();
                playSoundEffect();

                float bmi = calculateBMI(height, weight, isMetric);
                classifyBMI(bmi, history[recordCount].classification);

                // Save BMI record to history
                history[recordCount].height = height;
                history[recordCount].weight = weight;
                history[recordCount].bmi = bmi;
                recordCount++;

                printf("\nYour BMI: %.2f\n", bmi);
                printf("Classification: %s\n", history[recordCount - 1].classification);

                break;
            }
            case 2:
                if (recordCount > 0) {
                    displayHistory(history, recordCount);
                } else {
                    printf("\nNo records found!\n");
                }
                break;
            case 3:
                printf("\nThank you for using the BMI Calculator. Goodbye, %s!\n", name);
                return 0;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}
