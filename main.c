/*
 * Cargo Optimizer - Fractional Knapsack Solver
 * Optimal vehicle package loading using Greedy approach
 */

#include <stdio.h>

#define MAX 50

// Structure to store package attributes
struct Package
{
    int no;            // Package identification number
    float value;       // Profit / value of the package
    float weight;      // Weight of the package in kg
    float ratio;       // Profit-to-weight ratio (value / weight)
    float quantity;    // Fraction loaded into vehicle (0.0 to 1.0)
};

// Global state variables
struct Package p[MAX];
int n = 0;             // Total number of available packages
float capacity = 0;    // Maximum carrying capacity of vehicle
void enterDetails()
{
    int i;
    printf("\nEnter number of packages (1 to %d): ", MAX);
    scanf("%d", &n);
    getchar();

    if(n <= 0 || n > MAX)
    {
        printf("Invalid package count! Please enter a value between 1 and %d.\n", MAX);
        n = 0;
        return;
    }

    for(i = 0; i < n; i++)
    {
        p[i].no = i + 1;

        printf("\nPackage %d\n", i + 1);

        printf("Enter value/profit: ");
        scanf("%f", &p[i].value);

        printf("Enter weight: ");
        scanf("%f", &p[i].weight);

        while(p[i].weight <= 0)
        {
            printf("Weight must be greater than 0. Re-enter weight: ");
            scanf("%f", &p[i].weight);
        }

        p[i].ratio = 0;
        p[i].quantity = 0;
    }

    printf("\nEnter vehicle capacity: ");
    scanf("%f", &capacity);

    while(capacity <= 0)
    {
        printf("Capacity must be greater than 0. Re-enter vehicle capacity: ");
        scanf("%f", &capacity);
    }

    printf("\nPackage details entered successfully.\n");
}
void displayDetails()
{
    int i;
    if(n == 0)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }
    printf("\n+---------+--------------+--------------+--------------+\n");
    printf("| Package |    Value ($) |  Weight (kg) | Ratio ($/kg) |\n");
    printf("+---------+--------------+--------------+--------------+\n");
    for(i = 0; i < n; i++)
    {
        printf("|   %4d  | %12.2f | %12.2f | %12.2f |\n",
               p[i].no,
               p[i].value,
               p[i].weight,
               p[i].ratio);
    }
    printf("+---------+--------------+--------------+--------------+\n");
}
void calculateRatio()
{
    int i;
    if(n == 0)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }
    for(i = 0; i < n; i++)
    {
        p[i].ratio = p[i].value / p[i].weight;
    }
    printf("\nValue/Weight ratios calculated successfully.\n");
    displayDetails();
}
void sortPackages()
{
    int i, j;
    struct Package temp;
    if(n == 0)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }
    for(i = 0; i < n; i++)
    {
        p[i].ratio = p[i].value / p[i].weight;
    }
    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(p[j].ratio < p[j + 1].ratio)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    printf("\nPackages sorted by Value/Weight ratio (descending).\n");
    displayDetails();
}
void findMaximum()
{
    int i;
    float remaining;
    float totalValue = 0;
    float totalWeight = 0;
    if(n == 0)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }
    sortPackages();
    remaining = capacity;
    for(i = 0; i < n; i++)
    {
        p[i].quantity = 0;
        if(remaining >= p[i].weight)
        {
            p[i].quantity = 1;
            remaining = remaining - p[i].weight;
            totalWeight = totalWeight + p[i].weight;
            totalValue = totalValue + p[i].value;
        }
        else if(remaining > 0)
        {
            p[i].quantity = remaining / p[i].weight;
            totalWeight = totalWeight + remaining;
            totalValue = totalValue + (p[i].quantity * p[i].value);
            remaining = 0;
        }
    }
    float utilization = (capacity > 0) ? (totalWeight / capacity) * 100.0f : 0.0f;
    printf("\nMaximum Value Obtained : $%.2f\n", totalValue);
    printf("Total Weight Loaded    : %.2f kg\n", totalWeight);
    printf("Capacity Utilization   : %.2f%%\n", utilization);
}
void displaySelected()
{
    int i;
    float remaining;
    float totalValue = 0;
    float totalWeight = 0;
    if(n == 0)
    {
        printf("\nPlease enter package details first.\n");
        return;
    }
    sortPackages();
    remaining = capacity;
    printf("\n===================================================================\n");
    printf("                     OPTIMAL CARGO MANIFEST                        \n");
    printf("===================================================================\n");
    printf("+---------+--------------+--------------+--------------+----------+\n");
    printf("| Package | Fraction Taken| Weight (kg) | Profit Earned| Status   |\n");
    printf("+---------+--------------+--------------+--------------+----------+\n");
    for(i = 0; i < n; i++)
    {
        p[i].quantity = 0;
        if(remaining >= p[i].weight)
        {
            p[i].quantity = 1.0f;
            totalWeight += p[i].weight;
            totalValue += p[i].value;
            remaining -= p[i].weight;
            printf("|   %4d  |     100.0%%    | %12.2f | %12.2f | FULL     |\n",
                   p[i].no,
                   p[i].weight,
                   p[i].value);
        }
        else if(remaining > 0)
        {
            p[i].quantity = remaining / p[i].weight;
            totalWeight += remaining;
            totalValue += (p[i].quantity * p[i].value);
            printf("|   %4d  |     %5.1f%%    | %12.2f | %12.2f | FRACTION |\n",
                   p[i].no,
                   p[i].quantity * 100.0f,
                   remaining,
                   p[i].quantity * p[i].value);
            remaining = 0;
        }
    }
    float utilization = (capacity > 0) ? (totalWeight / capacity) * 100.0f : 0.0f;
    printf("+---------+--------------+--------------+--------------+----------+\n");
    printf("Vehicle Capacity       : %.2f kg\n", capacity);
    printf("Total Weight Loaded    : %.2f kg\n", totalWeight);
    printf("Capacity Utilization   : %.2f%%\n", utilization);
    printf("Maximum Cargo Value    : $%.2f\n", totalValue);
    printf("===================================================================\n");
}
void loadSampleData()
{
    n = 5;
    capacity = 60.0f;

    // Preset cargo packages: value, weight
    float sampleValues[5] = {280.0f, 100.0f, 120.0f, 120.0f, 240.0f};
    float sampleWeights[5] = {10.0f, 20.0f, 30.0f, 24.0f, 16.0f};

    for(int i = 0; i < n; i++)
    {
        p[i].no = i + 1;
        p[i].value = sampleValues[i];
        p[i].weight = sampleWeights[i];
        p[i].ratio = 0.0f;
        p[i].quantity = 0.0f;
    }

    printf("\nBenchmark dataset loaded successfully (5 packages, Capacity: %.2f kg).\n", capacity);
    displayDetails();
}
int main()
{
    int choice;
    do
    {
        printf("\n===================================================\n");
        printf("              CARGO DISPATCH OPTIMIZER             \n");
        printf("           (Fractional Knapsack Strategy)          \n");
        printf("===================================================\n");
        printf("  1. Enter Package Details\n");
        printf("  2. Display All Packages\n");
        printf("  3. Compute Value/Weight Ratios\n");
        printf("  4. Sort Packages by Ratio\n");
        printf("  5. Find Maximum Cargo Value\n");
        printf("  6. Display Optimal Cargo Manifest\n");
        printf("  7. Load Benchmark Sample Dataset\n");
        printf("  8. Exit\n");
        printf("===================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                enterDetails();
                break;
            case 2:
                displayDetails();
                break;
            case 3:
                calculateRatio();
                break;
            case 4:
                sortPackages();
                break;
            case 5:
                findMaximum();
                break;
            case 6:
                displaySelected();
                break;
            case 7:
                loadSampleData();
                break;
            case 8:
                printf("\nExiting Cargo Dispatch Optimizer. Safe transport!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while(choice != 8);
    return 0;
}
 
