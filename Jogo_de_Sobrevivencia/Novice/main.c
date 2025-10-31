#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITEMS 10

// Struct definition for an item
struct Item {
    char nome[30];
    char tipo[20]; // e.g., "weapon", "ammo", "health"
    int quantidade;
};

// Global backpack and item count
struct Item backpack[MAX_ITEMS];
int totalItens = 0;

// --- Function Prototypes ---
void insertItem();
void removeItem();
void listItems();
void findItem();
void clearBuffer();

int main() {
    int option;

    while (1) {
        // Display the menu
        printf("\n--- Initial Loot Backpack ---\n");
        printf("1. Add item\n");
        printf("2. Remove item\n");
        printf("3. List items\n");
        printf("4. Find item\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);
        clearBuffer(); // Clears the input buffer

        switch (option) {
            case 1:
                insertItem();
                break;
            case 2:
                removeItem();
                break;
            case 3:
                listItems();
                break;
            case 4:
                findItem();
                break;
            case 5:
                printf("Exiting the program.\n");
                return 0; // Exits the program
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return 0;
}

// Function to add a new item to the backpack
void insertItem() {
    if (totalItens >= MAX_ITEMS) {
        printf("The backpack is full. Cannot add more items.\n");
        return;
    }

    printf("\n--- Add New Item ---\n");
    printf("Item name: ");
    fgets(backpack[totalItens].nome, 30, stdin);
    backpack[totalItens].nome[strcspn(backpack[totalItens].nome, "\n")] = 0; // Remove newline

    printf("Item type (weapon, ammo, health): ");
    fgets(backpack[totalItens].tipo, 20, stdin);
    backpack[totalItens].tipo[strcspn(backpack[totalItens].tipo, "\n")] = 0; // Remove newline

    printf("Quantity: ");
    scanf("%d", &backpack[totalItens].quantidade);
    clearBuffer();

    totalItens++;
    printf("Item added successfully!\n");
}

// Function to remove an item by name
void removeItem() {
    char searchName[30];
    int i, found = -1;

    if (totalItens == 0) {
        printf("The backpack is empty.\n");
        return;
    }

    printf("\n--- Remove Item ---\n");
    printf("Name of the item to remove: ");
    fgets(searchName, 30, stdin);
    searchName[strcspn(searchName, "\n")] = 0; // Remove newline

    // Search for the item
    for (i = 0; i < totalItens; i++) {
        if (strcmp(backpack[i].nome, searchName) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        // Shift items to the left to fill the gap
        for (i = found; i < totalItens - 1; i++) {
            backpack[i] = backpack[i + 1];
        }
        totalItens--;
        printf("Item removed successfully!\n");
    } else {
        printf("Item not found in the backpack.\n");
    }
}

// Function to list all items in the backpack
void listItems() {
    if (totalItens == 0) {
        printf("The backpack is empty.\n");
        return;
    }

    printf("\n--- Items in Backpack ---\n");
    for (int i = 0; i < totalItens; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Name: %s\n", backpack[i].nome);
        printf("  Type: %s\n", backpack[i].tipo);
        printf("  Quantity: %d\n", backpack[i].quantidade);
    }
}

// Function to search for an item by name
void findItem() {
    char searchName[30];
    int i, found = 0;

    if (totalItens == 0) {
        printf("The backpack is empty.\n");
        return;
    }

    printf("\n--- Find Item ---\n");
    printf("Name of the item to find: ");
    fgets(searchName, 30, stdin);
    searchName[strcspn(searchName, "\n")] = 0; // Remove newline

    // Sequential search
    for (i = 0; i < totalItens; i++) {
        if (strcmp(backpack[i].nome, searchName) == 0) {
            printf("\n--- Item Found ---\n");
            printf("  Name: %s\n", backpack[i].nome);
            printf("  Type: %s\n", backpack[i].tipo);
            printf("  Quantity: %d\n", backpack[i].quantidade);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Item not found in the backpack.\n");
    }
}

// Function to clear the input buffer
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
