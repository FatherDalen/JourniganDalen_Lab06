#include <stdio.h>
#include <stdlib.h>

#define MONTHS 12

// Function prototypes
void readSales(float sales[]);
void displayMonthlySales(float sales[]);
void displaySalesSummary(float sales[]);
void displaySixMonthMovingAverage(float sales[]);
void displaySalesDescending(float sales[]);

int main() {
    float sales[MONTHS];

    // Read sales data from the input file
    readSales(sales);

    // Display reports
    printf("Monthly Sales Report for 2024\n");
    printf("=============================\n");
    displayMonthlySales(sales);
    printf("\nSales summary report:\n");
    displaySalesSummary(sales);
    printf("\nSix-Month moving average report:\n");
    displaySixMonthMovingAverage(sales);
    printf("\nSales report (highest to lowest):\n");
    displaySalesDescending(sales);

    return 0;
}

// Function to read sales data from an input file
void readSales(float sales[]) {
    FILE *file = fopen("sales_data.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        exit(1);
    }
    for (int i = 0; i < MONTHS; i++) {
        fscanf(file, "%f", &sales[i]);
    }
    fclose(file);
}

// Function to display the monthly sales report
void displayMonthlySales(float sales[]) {
    const char *months[] = {"January", "February", "March", "April", "May", "June",
                            "July", "August", "September", "October", "November", "December"};
    printf("Month\t\tSales\n");
    for (int i = 0; i < MONTHS; i++) {
        printf("%-10s\t%.2f\n", months[i], sales[i]);
    }
}

// Function to display the sales summary report
void displaySalesSummary(float sales[]) {
    float min = sales[0], max = sales[0], sum = 0.0;
    int minMonth = 0, maxMonth = 0;

    for (int i = 0; i < MONTHS; i++) {
        if (sales[i] < min) {
            min = sales[i];
            minMonth = i;
        }
        if (sales[i] > max) {
            max = sales[i];
            maxMonth = i;
        }
        sum += sales[i];
    }

    const char *months[] = {"January", "February", "March", "April", "May", "June",
                            "July", "August", "September", "October", "November", "December"};
    printf("Minimum sales: %.2f (%s)\n", min, months[minMonth]);
    printf("Maximum sales: %.2f (%s)\n", max, months[maxMonth]);
    printf("Average sales: %.2f\n", sum / MONTHS);
}

// Function to display the six-month moving average report
void displaySixMonthMovingAverage(float sales[]) {
    const char *months[] = {"January", "February", "March", "April", "May", "June",
                            "July", "August", "September", "October", "November", "December"};

    for (int i = 0; i <= MONTHS - 6; i++) {
        float sum = 0.0;
        for (int j = i; j < i + 6; j++) {
            sum += sales[j];
        }
        printf("%s-%s\t%.2f\n", months[i], months[i + 5], sum / 6);
    }
}

// Function to display the sales in descending order
void displaySalesDescending(float sales[]) {
    const char *months[] = {"January", "February", "March", "April", "May", "June",
                            "July", "August", "September", "October", "November", "December"};
    int indices[MONTHS];
    for (int i = 0; i < MONTHS; i++) {
        indices[i] = i;
    }

    // Sorting the sales in descending order along with month indices
    for (int i = 0; i < MONTHS - 1; i++) {
        for (int j = i + 1; j < MONTHS; j++) {
            if (sales[indices[i]] < sales[indices[j]]) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    printf("Month\t\tSales\n");
    for (int i = 0; i < MONTHS; i++) {
        printf("%-10s\t%.2f\n", months[indices[i]], sales[indices[i]]);
    }
}