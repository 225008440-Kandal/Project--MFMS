/* about.c */
#include <stdio.h>
#include <string.h>
#include "about.h"

#define MEMBERS 7
#define MAX_NAME 60

/* Group members, one string per member */
static char members[MEMBERS][MAX_NAME] = {
    "Kandal Muzemb 225008440 - Employee Management",
    " Christian Hatutale 225006812 - Budget Management",
    "Ilunga Bota 226141772 - Supplier Management",
    "Namholo Markus 224010646 - Asset Management",
    "N.E David 226100529 - Reports",
    "Nakale T willem 225036630 - Integration and Validation",
    "Franz Moussiessi 226141861 - About module, Testing and Git"
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
    int longest = 0;

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

    for (i = 0; i < MEMBERS; i++) {
        if ((int)strlen(members[i]) > longest) {
            longest = (int)strlen(members[i]);
        }
    }
    printf("\nTotal members: %d\n", MEMBERS);
    printf("Longest member entry: %d characters\n", longest);
}

void displayExit(void)
{
    printf("\n==========================================\n");
    printf("  Thank you for using the Municipal\n");
    printf("  Financial Management System.\n");
    printf("  Goodbye!\n");
    printf("==========================================\n");
}
