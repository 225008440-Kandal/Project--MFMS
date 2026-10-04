#include <stdio.h>

#include "reports.h"
#include "employees.h"
#include "budget.h"
#include "suppliers.h"
#include "assets.h"


// Employee report

static void employeeReport(void)
{
    int n;
    int i;

    double total = 0.0;
    double average;
    double highest;
    double lowest;

    n = getEmployeeCount();

    if (n == 0)
    {
        printf("\nNo employee records.\n");
        return;
    }

    
    highest = getEmployeeSalary(0);
    lowest = getEmployeeSalary(0);
    total = getEmployeeSalary(0);

    
    for (i = 1; i < n; i++)
    {
        double salary;

        salary = getEmployeeSalary(i);

        total = total + salary;

        if (salary > highest)
        {
            highest = salary;
        }

        if (salary < lowest)
        {
            lowest = salary;
        }
    }

    average = total / n;

    printf("EMPLOYEE REPORT\n");
    printf("Total Employees: %d\n", n);
    printf("Average Salary: %.2f\n", average);
    printf("Highest Salary: %.2f\n", highest);
    printf("Lowest Salary: %.2f\n", lowest);
}


static void budgetReport(void)
{
    int n;
    int i;
    int overCount = 0;

    double totalAllocated = 0.0;
    double totalSpent = 0.0;
    double remaining;

    n = getDepartmentCount();

    if (n == 0)
    {
        printf("\nNo budget records.\n");
        return;
    }

    // Calculation
    for (i = 0; i < n; i++)
    {
        totalAllocated = totalAllocated + getAllocated(i);
        totalSpent = totalSpent + getExpenditure(i);
    }

    remaining = totalAllocated - totalSpent;

    printf("\n--- BUDGET REPORT ---\n");
    printf("Total Allocated: N$%.2f\n", totalAllocated);
    printf("Total Expenditure: N$%.2f\n", totalSpent);
    printf("Remaining Budget: N$%.2f\n", remaining);

    printf("Departments Over Budget:\n");

    // Display department that exceeded their budget
    for (i = 0; i < n; i++)
    {
        if (getExpenditure(i) > getAllocated(i))
        {
            printf("- %s\n", getDepartmentName(i));
            overCount++;
        }
    }

    if (overCount == 0)
    {
        printf("None\n");
    }
}


static void supplierReport(void)
{
    int n;
    int i;

    n = getSupplierCount();

    if (n == 0)
    {
        printf("\nNo supplier records.\n");
        return;
    }

    printf("\n--- SUPPLIER REPORT ---\n");

    for (i = 0; i < n; i++)
    {
        printf("Supplier: %s | Town: %s\n",
               getSupplierName(i),
               getSupplierTown(i));
    }
}


static void assetReport(void)
{
    int n;
    int i;

    double totalValue = 0.0;

    n = getAssetCount();

    if (n == 0)
    {
        printf("\nNo asset records.\n");
        return;
    }

    printf("\n--- ASSET REPORT ---\n");

    for (i = 0; i < n; i++)
    {
        printf("Asset: %s | Value: N$%.2f\n",
               getAssetName(i),
               getAssetValue(i));

        totalValue = totalValue + getAssetValue(i);
    }

    printf("Total Asset Value: N$%.2f\n", totalValue);
}


// Menu

void reportsMenu(void)
{
    int choice;

    do
    {
        printf("\n--------------------------------\n");
        printf("             REPORTS\n");
        printf("-----------------------------------\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                employeeReport();
                break;

            case 2:
                budgetReport();
                break;

            case 3:
                supplierReport();
                break;

            case 4:
                assetReport();
                break;

            case 5:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);
}