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
    printf("\nEnter number of packages: ");
    scanf("%d", &n);
    getchar();
    for(i = 0; i < n; i++)
    {
        p[i].no = i + 1;
 
        printf("\nPackage %d\n", i + 1);
 
        printf("Enter value/profit: ");
        scanf("%f", &p[i].value);
 
        printf("Enter weight: ");
        scanf("%f", &p[i].weight);
 
        p[i].ratio = 0;
        p[i].quantity = 0;
    }
    printf("\nEnter vehicle capacity: ");
    scanf("%f", &capacity);
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
    printf("\n---------------------------------------------\n");
    printf("Package\tValue\tWeight\tRatio\n");
    printf("---------------------------------------------\n");
    for(i = 0; i < n; i++)
    {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               p[i].no,
               p[i].value,
               p[i].weight,
               p[i].ratio);
    }
 
    printf("---------------------------------------------\n");
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
    printf("\nPackage\tValue\tWeight\tRatio\n");
    for(i = 0; i < n; i++)
    {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               p[i].no,
               p[i].value,
               p[i].weight,
               p[i].ratio);
    }
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
    printf("\nPackages sorted according to Value/Weight ratio.\n");
    printf("\nPackage\tValue\tWeight\tRatio\n");
    for(i = 0; i < n; i++)
    {
        printf("%d\t%.2f\t%.2f\t%.2f\n",
               p[i].no,
               p[i].value,
               p[i].weight,
               p[i].ratio);
    }
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
            totalValue = totalValue +
                         (p[i].quantity * p[i].value);
            remaining = 0;
        }
    }
    printf("\nMaximum value = %.2f\n", totalValue);
    printf("Total weight used = %.2f\n", totalWeight);
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
    printf("\n-----------------------------------------------\n");
    printf("Selected Packages\n");
    printf("-----------------------------------------------\n");
    printf("Package\tQuantity\tWeight Used\tValue\n");
    printf("-----------------------------------------------\n");
    for(i = 0; i < n; i++)
    {
        p[i].quantity = 0;
        if(remaining >= p[i].weight)
        {
            p[i].quantity = 1;
            totalWeight = totalWeight + p[i].weight;
            totalValue = totalValue + p[i].value;
            remaining = remaining - p[i].weight;
            printf("%d\t%.2f\t\t%.2f\t\t%.2f\n",
                   p[i].no,
                   p[i].quantity,
                   p[i].weight,
                   p[i].value);
        }
        else if(remaining > 0)
        {
            p[i].quantity = remaining / p[i].weight;
 
            totalWeight = totalWeight + remaining;
            totalValue = totalValue +
                         (p[i].quantity * p[i].value);
            printf("%d\t%.2f\t\t%.2f\t\t%.2f\n",
                   p[i].no,
                   p[i].quantity,
                   remaining,
                   p[i].quantity * p[i].value);
 
            remaining = 0;
        }
    }
    printf("-----------------------------------------------\n");
    printf("Total Weight Used : %.2f\n", totalWeight);
    printf("Maximum Value     : %.2f\n", totalValue);
}
int main()
{
    int choice;
    do
    {
        printf("\n\n========== FRACTIONAL KNAPSACK ==========\n");
        printf("1. Enter Package Details\n");
        printf("2. Display Package Details\n");
        printf("3. Calculate Value/Weight Ratio\n");
        printf("4. Sort Packages by Ratio\n");
        printf("5. Find Maximum Value\n");
        printf("6. Display Selected Packages\n");
        printf("7. Exit\n");
        printf("=========================================\n");
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
                printf("\nProgram ended.\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while(choice != 7);
    return 0;
}
 
