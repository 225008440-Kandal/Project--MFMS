#include <stdio.h>
#include <string.h>
#include "suppliers.h"


#define MAX_SUPPLIERS 50
#define MAX_NAME 50
#define MAX_CONTACT 30

static int ids[MAX_SUPPLIERS];
static char names[MAX_SUPPLIERS][MAX_NAME];
static char emails[MAX_SUPPLIERS][MAX_NAME];
static char phones[MAX_SUPPLIERS][MAX_CONTACT];
static char towns[MAX_SUPPLIERS][MAX_NAME];
static int count = 0;


static void showSupplierDescription(int i)
{
    char description[MAX_NAME * 2 + 20];

    strcpy(description, names[i]);
    strcat(description, " operates in ");
    strcat(description, towns[i]);
    strcat(description, ".");

    printf("Description: %s\n", description);
}
/* ---- private helpers ---- */

static void addSupplier(void)
{
    if (count == MAX_SUPPLIERS)
    {
        printf("Supplier list is full.\n");
        return;
    }

    printf("Enter supplier ID: ");
    scanf("%d", &ids[count]);
    getchar();

    printf("Enter supplier name: ");
    fgets(names[count], MAX_NAME, stdin);
    names[count][strcspn(names[count], "\n")] = '\0';

    if (strlen(names[count]) == 0)
    {
        printf("Supplier name cannot be empty.\n");
        return;
    }

    printf("Enter supplier email: ");
    fgets(emails[count], MAX_NAME, stdin);
    emails[count][strcspn(emails[count], "\n")] = '\0';

    printf("Enter supplier telephone: ");
    fgets(phones[count], MAX_CONTACT, stdin);
    phones[count][strcspn(phones[count], "\n")] = '\0';

    printf("Enter supplier town: ");
    fgets(towns[count], MAX_NAME, stdin);
    towns[count][strcspn(towns[count], "\n")] = '\0';

    count++;

    printf("Supplier added successfully.\n");
}

static void displaySuppliers(void)
{
    if (count == 0)
    {
        printf("No suppliers available.\n");
        return;
    }

    printf("\n%-5s %-20s %-30s %-15s %-20s\n",
           "ID", "Name", "Email", "Phone", "Town");

    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        printf("%-5d %-20s %-30s %-15s %-20s\n",
               ids[i], names[i], emails[i], phones[i], towns[i]);
    }
}

static void searchSupplier(void)
{
    char searchName[MAX_NAME];
    int found = 0;

    printf("Enter supplier name to search: ");
    fgets(searchName, MAX_NAME, stdin);
    searchName[strcspn(searchName, "\n")] = '\0';

    for (int i = 0; i < count; i++)
    {
        if (strcmp(names[i], searchName) == 0)
        {
            printf("\nSupplier found:\n");
            printf("ID: %d\n", ids[i]);
            printf("Name: %s\n", names[i]);
            printf("Email: %s\n", emails[i]);
            printf("Phone: %s\n", phones[i]);
            printf("Town: %s\n", towns[i]);
            showSupplierDescription(i);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Supplier not found.\n");
    }
}

static void displayByTown(void)
{
    char searchTown[MAX_NAME];
    int found = 0;

    printf("Enter town: ");
    fgets(searchTown, MAX_NAME, stdin);
    searchTown[strcspn(searchTown, "\n")] = '\0';

    for (int i = 0; i < count; i++)
    {
        if (strcmp(towns[i], searchTown) == 0)
        {
            printf("\nID: %d\n", ids[i]);
            printf("Name: %s\n", names[i]);
            printf("Email: %s\n", emails[i]);
            printf("Phone: %s\n", phones[i]);
            printf("Town: %s\n", towns[i]);
            


            found = 1;
        }
    }

    if (!found)
    {
        printf("No suppliers found in this town.\n");
    }
}

/* ---- public ---- */

void supplierMenu(void)
{
    int choice;

    do
    {
        printf("\n===== SUPPLIER MANAGEMENT =====\n");
        printf("1. Add Supplier\n");
        printf("2. Display All Suppliers\n");
        printf("3. Search Supplier\n");
        printf("4. Display Suppliers By Town\n");
        printf("5. Back\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
            case 1:
                addSupplier();
                break;

            case 2:
                displaySuppliers();
                break;

            case 3:
                searchSupplier();
                break;

            case 4:
                displayByTown();
                break;

            case 5:
                printf("Returning to main menu...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);
}

int getSupplierCount(void) {
    return count;
}

const char* getSupplierName(int i)
{
    return names[i];
}

const char* getSupplierTown(int i)
{
    return towns[i];
}
