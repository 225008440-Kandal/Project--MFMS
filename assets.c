#include <stdio.h>
#include <string.h>
#include "assets.h"
#include "utils.h"
 
#define MAX_ASSETS 50
#define MAX_NAME   50
 

static int    ids[MAX_ASSETS];
static char   names[MAX_ASSETS][MAX_NAME];
static char   types[MAX_ASSETS][MAX_NAME];
static double values[MAX_ASSETS];
static char   departments[MAX_ASSETS][MAX_NAME];
static char   conditions[MAX_ASSETS][MAX_NAME];
 
static int count = 0;    
 
 

static void addAsset(void)
{
    printHeading("REGISTER ASSET");
 
    if (count == MAX_ASSETS) {
        printf("The asset register is full (%d assets).\n", MAX_ASSETS);
        return;
    }
 
    ids[count] = readInt("Asset ID              : ", 1, 99999);
    readText("Asset name            : ", names[count],       MAX_NAME);
    readText("Asset type            : ", types[count],       MAX_NAME);
    values[count] = readMoney("Purchase value    N$: ");
    readText("Department            : ", departments[count], MAX_NAME);
    readText("Condition             : ", conditions[count],  MAX_NAME);
 
    count++;
 
    printf("\nAsset registered. Total assets: %d\n", count);
}
 
 

static void displayAssets(void)
{
    int i;
    double total = 0;
 
    printHeading("MUNICIPAL ASSET REGISTER");
 
    if (count == 0) {
        printf("No assets have been registered yet.\n");
        return;
    }
 
    printf("%-6s %-18s %-14s %14s %-14s %s\n",
           "ID", "ASSET", "TYPE", "VALUE", "DEPARTMENT", "CONDITION");
    printf("---------------------------------------------------------------------------------\n");
 
    for (i = 0; i < count; i++) {
        printf("%-6d %-18s %-14s %14.2f %-14s %s\n",
               ids[i], names[i], types[i], values[i],
               departments[i], conditions[i]);
 
        total = total + values[i];      
    }
 
    printf("---------------------------------------------------------------------------------\n");
    printf("Total assets: %d          Total value: N$%.2f\n", count, total);
}
 
 

static void searchAsset(void)
{
    char target[MAX_NAME];
    int i;
    int found = 0;
 
    printHeading("SEARCH ASSET");
 
    if (count == 0) {
        printf("No assets have been registered yet.\n");
        return;
    }
 
    readText("Enter the asset name: ", target, MAX_NAME);
 
    for (i = 0; i < count; i++) {
 
        
        if (strcmp(names[i], target) == 0) {
            printf("\nAsset found at position %d:\n", i);
            printf("  Asset ID       : %d\n",     ids[i]);
            printf("  Asset name     : %s\n",     names[i]);
            printf("  Asset type     : %s\n",     types[i]);
            printf("  Purchase value : N$%.2f\n", values[i]);
            printf("  Department     : %s\n",     departments[i]);
            printf("  Condition      : %s\n",     conditions[i]);
 
            found = 1;
            break;
        }
    }
 
    if (found == 0) {
        printf("\nNo asset named \"%s\" was found.\n", target);
        printf("Note: the search is case sensitive.\n");
    }
}
 
 

static void displayTotalValue(void)
{
    int i;
    double total = 0;
 
    printHeading("TOTAL ASSET VALUE");
 
    if (count == 0) {
        printf("No assets have been registered yet.\n");
        return;
    }
 
    for (i = 0; i < count; i++) {
        total = total + values[i];
    }
 
    printf("Number of assets    : %d\n",      count);
    printf("Total asset value   : N$%.2f\n",  total);
    printf("Average asset value : N$%.2f\n",  total / count);
}
 
 

static void displayByDepartment(void)
{
    char target[MAX_NAME];
    int i;
    int matches = 0;
    double subTotal = 0;
 
    printHeading("ASSETS BY DEPARTMENT");
 
    if (count == 0) {
        printf("No assets have been registered yet.\n");
        return;
    }
 
    readText("Enter the department name: ", target, MAX_NAME);
 
    for (i = 0; i < count; i++) {
        if (strcmp(departments[i], target) == 0) {
            printf("  %-18s %-14s N$%.2f (%s)\n",
                   names[i], types[i], values[i], conditions[i]);
            subTotal = subTotal + values[i];
            matches++;
        }
    }
 
    if (matches == 0) {
        printf("  No assets are registered to \"%s\".\n", target);
    } else {
        printf("\n%d asset(s) in %s, worth N$%.2f in total.\n",
               matches, target, subTotal);
    }
}
 
 

void assetMenu(void)
{
    int choice;
 
    do {
        printf("\n----------------------------------\n");
        printf("       ASSET MANAGEMENT\n");
        printf("----------------------------------\n");
        printf("1. Register asset\n");
        printf("2. Display asset register\n");
        printf("3. Search asset\n");
        printf("4. Total asset value\n");
        printf("5. Assets by department\n");
        printf("6. Back to main menu\n\n");
 
        choice = readInt("Enter your choice: ", 1, 6);
 
        switch (choice) {
            case 1: addAsset();           break;
            case 2: displayAssets();      break;
            case 3: searchAsset();        break;
            case 4: displayTotalValue();  break;
            case 5: displayByDepartment();break;
            case 6: printf("Returning to the main menu...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
 
    } while (choice != 6);
}
 
 

 
int getAssetCount(void)
{
    return count;
}
 
const char* getAssetName(int i)
{
    if (i < 0 || i >= count) {
        return "";
    }
    return names[i];
}
 
double getAssetValue(int i)
{
    if (i < 0 || i >= count) {
        return 0;
    }
    return values[i];
}