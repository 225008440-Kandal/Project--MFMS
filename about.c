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
    /* TODO: print a banner box with the system name.
       Suggestion:
       ==========================================
         MUNICIPAL FINANCIAL MANAGEMENT SYSTEM
         PAP521S - Project A - Group <number>
       ==========================================
       Use \n for line breaks. */
}

void displayAbout(void)
{
    int i;

    /* TODO: print the system name, group number and a short
       description of what the system does */

    printf("\nGroup members and responsibilities:\n");
    /* A for loop over the array - one line per member. */
    for (i = 0; i < MEMBERS; i++) {
        printf("  %d. %s\n", i + 1, members[i]);
    }

    /* TODO: print one line per module explaining what it does,
       so a new user knows what each menu option is for */

    /* TODO (optional, shows strlen): print how many members there are
       and the length of the longest name */
}

void displayExit(void)
{
    /* TODO: print a short goodbye message with the system name */
}
