

#include <stdio.h>

#include "employees.h"   /* Employee Management  */
#include "budget.h"      /* Budget Management    */
#include "suppliers.h"   /* Supplier Management  */
#include "assets.h"      /* Asset Management     */
#include "reports.h"     /* Reports              */
#include "about.h"       /* About / Help         */
#include "utils.h"       /* shared input helpers */

/* 'static' keeps this function private to main.c. */
static void displayMainMenu(void)
{
    printf("\n========================================\n");
    printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("========================================\n\n");
    printf("1. Employee Management\n");
    printf("2. Budget Management\n");
    printf("3. Supplier Management\n");
    printf("4. Asset Management\n");
    printf("5. Reports\n");
    printf("6. About / Help\n");
    printf("7. Exit\n\n");
}

int main(void)
{
    int choice;

    displayWelcome();       
    do {
        displayMainMenu();

       
        choice = readInt("Enter your choice: ", 1, 7);

       
        switch (choice) {
            case 1:
                employeeMenu();
                break;
            case 2:
                budgetMenu();
                break;
            case 3:
                supplierMenu();
                break;
            case 4:
                assetMenu();
                break;
            case 5:
                reportsMenu();
                break;
            case 6:
                displayAbout();
                break;
            case 7:
                displayExit();
                break;
            default:
              
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}