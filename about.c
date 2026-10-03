/* about.c */
#include <stdio.h>
#include <string.h>
#include "about.h"

#define MEMBERS 7
#define MAX_NAME 60

/* An array of strings holding the group members.
   Using an array plus a loop here (instead of seven printf lines)
   is what demonstrates arrays and loops in your own code -
   be ready to explain that choice to the lecturer. */
static char members[MEMBERS][MAX_NAME] = {
    "Student 1 - Employee Management",
    "Student 2 - Budget Management",
    "Student 3 - Supplier Management",
    "Student 4 - Asset Management",
    "Student 5 - Reports",
    "Student 6 - Integration and Validation",
    "Student 7 - About module, Testing and Git"
    /* TODO: replace these with the real names and student numbers */
};

void displayWelcome(void)
{
    printf("\n==========================================\n");
    printf("  MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("  PAP521S - Project A - Group  x\n");
    printf("==========================================\n\n");
}
void displayAbout(void)
{
    int i;

    printf("\n========== ABOUT / HELP ==========\n");
    printf("Municipal Financial Management System\n");
    printf("PAP521S - Project A - Group x\n");
    printf("A console program that manages employees, budgets,\n");
    printf("suppliers and assets of a municipality, and\n");
    printf("produces summary reports.\n");

    printf("\nGroup members and responsibilities:\n");
    /* A for loop over the array - one line per member. */
    for (i = 0; i < MEMBERS; i++) {
        printf("  %d. %s\n", i + 1, members[i]);
    }

    printf("\nWhat each menu option does:\n");
    printf("  1. Employees - add, view and search employee records\n");
    printf("  2. Budget    - manage department budgets\n");
    printf("  3. Suppliers - manage supplier records\n");
    printf("  4. Assets    - manage municipal assets\n");
    printf("  5. Reports   - show summary reports\n");
    printf("  6. About     - show this help screen\n");
    printf("  7. Exit      - close the program\n");

    /* TODO (optional, shows strlen): print how many members there are
       and the length of the longest name */
}

void displayExit(void)
{
    printf("\n==========================================\n");
    printf("  Thank you for using the Municipal\n");
    printf("  Financial Management System.\n");
    printf("  Goodbye!\n");
    printf("==========================================\n");
}
