/* ============================================================
   employees.c  -  Employee Management module
   PAP521S Project A - Municipal Financial Management System

   What this module does:
     - add an employee
     - display all employees
     - search for an employee by name
     - calculate salary information (gross and net)
     - expose employee data to reports.c through getters

   C concepts used here: variables, data types, operators,
   if/else, switch, while and for loops, arrays, strings
   (strlen, strcmp, strcpy, strcat) and functions.
   ============================================================ */

#include <stdio.h>      /* printf, scanf, fgets  */
#include <string.h>     /* strlen, strcmp, strcpy, strcat, strcspn */
#include "employees.h"  /* our own header - so the compiler checks that the
                           functions we write here match what we promised */

/* ---------- constants ----------
   #define creates a named constant. Using MAX_EMPLOYEES everywhere
   instead of the bare number 50 means we change it in ONE place. */
#define MAX_EMPLOYEES 50
#define MAX_NAME      50
#define TAX_RATE      0.15   /* 15% tax, used in the net salary calculation */

/* ---------- the data ----------
   Structures are not covered in Weeks 1-8, so we use PARALLEL ARRAYS:
   one array per field, all sharing the same index.
   Employee number 0 is ids[0] + names[0] + basicSalary[0] ... and so on.

   'static' makes these private to this file. Other modules cannot touch
   them directly - they must go through our functions. That is why two
   people can both have a variable called 'count' without the compiler
   complaining. */
static int    ids[MAX_EMPLOYEES];
static char   names[MAX_EMPLOYEES][MAX_NAME];        /* array of strings  */
static char   departments[MAX_EMPLOYEES][MAX_NAME];
static double basicSalary[MAX_EMPLOYEES];
static double housing[MAX_EMPLOYEES];
static double transport[MAX_EMPLOYEES];

static int count = 0;   /* how many employees are actually stored.
                           Starts at 0 and grows as we add people. */


/* ============================================================
   SECTION 1 - input helpers

   These read user input safely. They are 'static' because they are
   only used inside this file.

   THE CLASSIC C TRAP they solve: scanf("%d", &x) reads the number but
   leaves the Enter key (the '\n') sitting in the input buffer. The next
   fgets() then reads that leftover newline, sees an empty line, and the
   program appears to SKIP a question. getchar() eats that leftover.
   ============================================================ */

/* Reads a whole line of text into 'out' and removes the newline. */
static void readLine(const char *prompt, char *out, int size)
{
    printf("%s", prompt);
    fgets(out, size, stdin);

    /* fgets keeps the '\n' you typed when pressing Enter.
       If we leave it, "John" is actually stored as "John\n" and
       strcmp will never match it against "John".
       strcspn(out, "\n") returns the position of the '\n', and we
       overwrite it with '\0', the end-of-string marker. */
    out[strcspn(out, "\n")] = '\0';
}

/* Reads a name and refuses an empty one (validation requirement). */
static void readName(const char *prompt, char *out, int size)
{
    /* do...while runs the body at least once, then repeats while the
       condition is true. Perfect for "keep asking until it is valid". */
    do {
        readLine(prompt, out, size);

        /* strlen() returns the number of characters in a string.
           If it is 0, the user just pressed Enter without typing. */
        if (strlen(out) == 0) {
            printf("  Error: this cannot be empty. Please try again.\n");
        }
    } while (strlen(out) == 0);
}

/* Reads an integer and keeps asking until it is between min and max. */
static int readInt(const char *prompt, int min, int max)
{
    int value;
    int ch;

    while (1) {                       /* 1 is always true -> infinite loop, */
        printf("%s", prompt);         /* we leave it with 'return'          */

        /* scanf returns how many values it successfully read.
           If the user typed letters, it returns 0 and the letters
           stay stuck in the buffer - so we must clear them or the
           program loops forever printing the same error. */
        if (scanf("%d", &value) != 1) {
            while ((ch = getchar()) != '\n' && ch != EOF) { }   /* clear buffer */
            printf("  Error: please enter a number.\n");
            continue;                 /* go back to the top of the loop */
        }

        while ((ch = getchar()) != '\n' && ch != EOF) { }  /* eat the Enter key */

        if (value >= min && value <= max) {   /* && is the logical AND operator */
            return value;
        }

        printf("  Error: please enter a value between %d and %d.\n", min, max);
    }
}

/* Reads an amount of money and refuses negative values
   (the brief requires that negative salaries are rejected). */
static double readMoney(const char *prompt)
{
    double value;
    int ch;

    while (1) {
        printf("%s", prompt);

        /* NOTE: a double is read with %lf in scanf,
           but printed with %.2f in printf. Mixing them up
           gives completely wrong numbers. */
        if (scanf("%lf", &value) != 1) {
            while ((ch = getchar()) != '\n' && ch != EOF) { }
            printf("  Error: please enter a number.\n");
            continue;
        }

        while ((ch = getchar()) != '\n' && ch != EOF) { }

        if (value < 0) {
            printf("  Error: the amount cannot be negative.\n");
            continue;
        }

        return value;
    }
}


/* ============================================================
   SECTION 2 - salary calculations

   These are pure calculation functions: they take values in
   through their PARAMETERS and give a value back with 'return'.
   They touch no arrays, which makes them easy to test and to explain.
   ============================================================ */

/* Gross salary = basic + housing allowance + transport allowance.
   This is the Week 3 formula from the Employee Salary Calculator lab. */
static double calculateGross(double basic, double house, double trans)
{
    return basic + house + trans;
}

/* Net salary = gross - tax, where tax is 15% of the gross. */
static double calculateNet(double gross)
{
    return gross - (gross * TAX_RATE);
}


/* ============================================================
   SECTION 3 - the operations

   Each menu option is one function. That is what the brief means by
   "the system must not be one very large main() function".
   ============================================================ */

/* ---- Add an employee ---- */
static void addEmployee(void)
{
    printf("\n--- ADD EMPLOYEE ---\n");

    /* An array has a fixed size. Writing past the end corrupts memory,
       so we must refuse when the list is full. */
    if (count == MAX_EMPLOYEES) {
        printf("The employee list is full (%d employees).\n", MAX_EMPLOYEES);
        return;               /* leave the function early */
    }

    /* We write at index [count] - the first free slot -
       then increase count at the end. */
    ids[count]         = readInt("Employee ID           : ", 1, 99999);
    readName           ("Name                  : ", names[count], MAX_NAME);
    readName           ("Department            : ", departments[count], MAX_NAME);
    basicSalary[count] = readMoney("Basic salary        N$: ");
    housing[count]     = readMoney("Housing allowance   N$: ");
    transport[count]   = readMoney("Transport allowance N$: ");

    count++;              /* one more employee stored */

    printf("\nEmployee added successfully. Total employees: %d\n", count);
}

/* ---- Display all employees ---- */
static void displayEmployees(void)
{
    int i;
    double gross, net;
    char label[MAX_NAME * 2 + 10];   /* room for "Name (Department)" */

    printf("\n--- ALL EMPLOYEES ---\n");

    /* Always guard the empty case, otherwise the user sees an
       empty table and thinks the program is broken. */
    if (count == 0) {
        printf("No employees have been added yet.\n");
        return;
    }

    /* %-20s means: print a string, left-aligned, padded to 20 characters.
       That is what lines the columns up. */
    printf("%-6s %-20s %-15s %12s %12s\n",
           "ID", "NAME", "DEPARTMENT", "GROSS", "NET");
    printf("--------------------------------------------------------------------------\n");

    /* A 'for' loop is the right choice here: we know exactly how many
       times to repeat - once per stored employee. */
    for (i = 0; i < count; i++) {
        gross = calculateGross(basicSalary[i], housing[i], transport[i]);
        net   = calculateNet(gross);

        printf("%-6d %-20s %-15s %12.2f %12.2f\n",
               ids[i], names[i], departments[i], gross, net);
    }

    printf("--------------------------------------------------------------------------\n");
    printf("Total employees: %d\n", count);

    /* strcpy and strcat demonstrated on real data:
       strcpy COPIES a string into another, strcat APPENDS to it.
       Here we build the label "Name (Department)" for the last employee. */
    strcpy(label, names[count - 1]);      /* label = "John"               */
    strcat(label, " (");                  /* label = "John ("             */
    strcat(label, departments[count - 1]);/* label = "John (Finance"      */
    strcat(label, ")");                   /* label = "John (Finance)"     */
    printf("Most recently added: %s\n", label);
}

/* ---- Search for an employee by name ---- */
static void searchEmployee(void)
{
    char target[MAX_NAME];
    int i;
    int found = 0;      /* a "flag": 0 means not found yet, 1 means found */
    double gross, net;

    printf("\n--- SEARCH EMPLOYEE ---\n");

    if (count == 0) {
        printf("No employees have been added yet.\n");
        return;
    }

    readName("Enter the employee name to search: ", target, MAX_NAME);

    for (i = 0; i < count; i++) {

        /* You CANNOT compare strings with == in C. That would compare
           two memory addresses, not the text, and would never match.
           strcmp() compares the actual characters and returns 0 when
           the two strings are identical - which feels backwards, but
           read it as "zero difference between them". */
        if (strcmp(names[i], target) == 0) {

            gross = calculateGross(basicSalary[i], housing[i], transport[i]);
            net   = calculateNet(gross);

            printf("\nEmployee found at position %d:\n", i);
            printf("  ID                  : %d\n",      ids[i]);
            printf("  Name                : %s\n",      names[i]);
            printf("  Department          : %s\n",      departments[i]);
            printf("  Basic salary        : N$%.2f\n",  basicSalary[i]);
            printf("  Housing allowance   : N$%.2f\n",  housing[i]);
            printf("  Transport allowance : N$%.2f\n",  transport[i]);
            printf("  Gross salary        : N$%.2f\n",  gross);
            printf("  Tax (15%%)           : N$%.2f\n", gross * TAX_RATE);
            printf("  Net salary          : N$%.2f\n",  net);

            found = 1;
            break;      /* stop the loop - we already found the employee */
        }
    }

    /* The flag tells us what happened after the loop finished. */
    if (found == 0) {
        printf("\nNo employee named \"%s\" was found.\n", target);
        printf("Note: the search is case sensitive - \"john\" is not \"John\".\n");
    }
}

/* ---- Salary summary for this module ---- */
static void salarySummary(void)
{
    int i;
    double gross, total = 0, highest, lowest, average;

    printf("\n--- SALARY SUMMARY ---\n");

    if (count == 0) {
        printf("No employees have been added yet.\n");
        return;   /* this guard also stops a division by zero below */
    }

    /* IMPORTANT: highest and lowest are initialised from the FIRST
       employee, not from 0. Salaries are positive, so if lowest started
       at 0 no salary would ever be "less than 0" and it would print
       0.00 forever. */
    highest = calculateGross(basicSalary[0], housing[0], transport[0]);
    lowest  = highest;

    for (i = 0; i < count; i++) {
        gross = calculateGross(basicSalary[i], housing[i], transport[i]);

        total = total + gross;

        if (gross > highest) {
            highest = gross;
        }
        if (gross < lowest) {
            lowest = gross;
        }
    }

    average = total / count;

    printf("Total employees : %d\n",      count);
    printf("Total payroll   : N$%.2f\n",  total);
    printf("Average salary  : N$%.2f\n",  average);
    printf("Highest salary  : N$%.2f\n",  highest);
    printf("Lowest salary   : N$%.2f\n",  lowest);
}


/* ============================================================
   SECTION 4 - the module menu

   This is the only function main.c calls. Everything above is
   private to this file.
   ============================================================ */

void employeeMenu(void)
{
    int choice;

    do {
        printf("\n==================================\n");
        printf("      EMPLOYEE MANAGEMENT\n");
        printf("==================================\n");
        printf("1. Add employee\n");
        printf("2. Display all employees\n");
        printf("3. Search employee\n");
        printf("4. Salary summary\n");
        printf("5. Back to main menu\n\n");

        choice = readInt("Enter your choice: ", 1, 5);

        /* A switch is the clearest way to choose one action out of
           several menu options. Each 'break' stops the switch -
           without it, execution would fall through into the next case. */
        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                displayEmployees();
                break;
            case 3:
                searchEmployee();
                break;
            case 4:
                salarySummary();
                break;
            case 5:
                printf("Returning to the main menu...\n");
                break;
            default:
                /* readInt already blocks anything outside 1-5, so this
                   should never run - but a default case is good practice
                   and the brief requires invalid choices to be handled. */
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);      /* repeat until the user chooses to go back */
}


/* ============================================================
   SECTION 5 - getters used by reports.c

   reports.c stores no data of its own. It reads ours through these
   three functions. This is why our arrays can stay 'static'.
   ============================================================ */

int getEmployeeCount(void)
{
    return count;
}

double getEmployeeSalary(int i)
{
    /* Defensive check: if reports.c ever asks for an index that does
       not exist, we return 0 instead of reading memory we do not own. */
    if (i < 0 || i >= count) {
        return 0;
    }
    return calculateGross(basicSalary[i], housing[i], transport[i]);
}

const char* getEmployeeName(int i)
{
    if (i < 0 || i >= count) {
        return "";
    }
    return names[i];
}
