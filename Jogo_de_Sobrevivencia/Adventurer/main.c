#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Struct Definitions ---
// Struct for an item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Struct for a node in the linked list
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// --- Vector (Array) Functions ---
void insertItemVector(Item vector[], int* total);
void removeItemVector(Item vector[], int* total);
void listItemsVector(const Item vector[], int total);
void sequentialSearchVector(const Item vector[], int total);
void sortVector(Item vector[], int total);
void binarySearchVector(const Item vector[], int total);

// --- Linked List Functions ---
void insertItemList(No** start);
void removeItemList(No** start);
void listItemsList(const No* start);
void sequentialSearchList(const No* start);
void freeList(No* start);

// --- Utility Functions ---
void clearBuffer();

int main() {
    // Vector implementation
    Item backpackVector[10]; // Static vector with capacity for 10 items
    int totalVector = 0;

    // Linked list implementation
    No* backpackList = NULL; // Head of the linked list

    int option, subOption;

    while (1) {
        printf("\n--- Comparison: Vector vs. Linked List ---\n");
        printf("1. Manage Backpack with Vector\n");
        printf("2. Manage Backpack with Linked List\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);
        clearBuffer();

        switch (option) {
            case 1: // --- Vector Menu ---
                do {
                    printf("\n--- Backpack with Vector ---\n");
                    printf("1. Insert item\n");
                    printf("2. Remove item\n");
                    printf("3. List items\n");
                    printf("4. Search (Sequential)\n");
                    printf("5. Sort and Search (Binary)\n");
                    printf("6. Back\n");
                    printf("Choose an option: ");
                    scanf("%d", &subOption);
                    clearBuffer();

                    switch (subOption) {
                        case 1: insertItemVector(backpackVector, &totalVector); break;
                        case 2: removeItemVector(backpackVector, &totalVector); break;
                        case 3: listItemsVector(backpackVector, totalVector); break;
                        case 4: sequentialSearchVector(backpackVector, totalVector); break;
                        case 5:
                            sortVector(backpackVector, totalVector);
                            binarySearchVector(backpackVector, totalVector);
                            break;
                        case 6: break;
                        default: printf("Invalid option.\n");
                    }
                } while (subOption != 6);
                break;

            case 2: // --- Linked List Menu ---
                do {
                    printf("\n--- Backpack with Linked List ---\n");
                    printf("1. Insert item\n");
                    printf("2. Remove item\n");
                    printf("3. List items\n");
                    printf("4. Search (Sequential)\n");
                    printf("5. Back\n");
                    printf("Choose an option: ");
                    scanf("%d", &subOption);
                    clearBuffer();

                    switch (subOption) {
                        case 1: insertItemList(&backpackList); break;
                        case 2: removeItemList(&backpackList); break;
                        case 3: listItemsList(backpackList); break;
                        case 4: sequentialSearchList(backpackList); break;
                        case 5: break;
                        default: printf("Invalid option.\n");
                    }
                } while (subOption != 5);
                break;

            case 3:
                freeList(backpackList);
                printf("Exiting the program.\n");
                return 0;

            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return 0;
}

// --- Vector Function Implementations ---
void insertItemVector(Item vector[], int* total) {
    if (*total >= 10) {
        printf("Backpack (vector) is full.\n");
        return;
    }
    printf("Item name: ");
    fgets(vector[*total].nome, 30, stdin);
    vector[*total].nome[strcspn(vector[*total].nome, "\n")] = 0;
    printf("Type: ");
    fgets(vector[*total].tipo, 20, stdin);
    vector[*total].tipo[strcspn(vector[*total].tipo, "\n")] = 0;
    printf("Quantity: ");
    scanf("%d", &vector[*total].quantidade);
    clearBuffer();
    (*total)++;
}

void removeItemVector(Item vector[], int* total) {
    char name[30];
    printf("Name of the item to remove: ");
    fgets(name, 30, stdin);
    name[strcspn(name, "\n")] = 0;
    int i, j, found = 0;
    for (i = 0; i < *total; i++) {
        if (strcmp(vector[i].nome, name) == 0) {
            for (j = i; j < *total - 1; j++) {
                vector[j] = vector[j + 1];
            }
            (*total)--;
            found = 1;
            printf("Item removed.\n");
            break;
        }
    }
    if (!found) printf("Item not found.\n");
}

void listItemsVector(const Item vector[], int total) {
    printf("\n--- Items in Vector ---\n");
    for (int i = 0; i < total; i++) {
        printf("Name: %s, Type: %s, Qty: %d\n", vector[i].nome, vector[i].tipo, vector[i].quantidade);
    }
}

void sequentialSearchVector(const Item vector[], int total) {
    char name[30];
    printf("Name of the item to search: ");
    fgets(name, 30, stdin);
    name[strcspn(name, "\n")] = 0;
    int comparisons = 0;
    for (int i = 0; i < total; i++) {
        comparisons++;
        if (strcmp(vector[i].nome, name) == 0) {
            printf("Item found! Comparisons: %d\n", comparisons);
            return;
        }
    }
    printf("Item not found. Comparisons: %d\n", comparisons);
}

void sortVector(Item vector[], int total) {
    // Bubble Sort
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (strcmp(vector[j].nome, vector[j + 1].nome) > 0) {
                Item temp = vector[j];
                vector[j] = vector[j + 1];
                vector[j + 1] = temp;
            }
        }
    }
    printf("Vector sorted.\n");
}

void binarySearchVector(const Item vector[], int total) {
    char name[30];
    printf("Name of the item to search (binary): ");
    fgets(name, 30, stdin);
    name[strcspn(name, "\n")] = 0;
    int start = 0, end = total - 1, middle, comparisons = 0;
    while (start <= end) {
        middle = start + (end - start) / 2;
        comparisons++;
        int res = strcmp(vector[middle].nome, name);
        if (res == 0) {
            printf("Item found! Comparisons: %d\n", comparisons);
            return;
        }
        if (res < 0) start = middle + 1;
        else end = middle - 1;
    }
    printf("Item not found. Comparisons: %d\n", comparisons);
}

// --- Linked List Function Implementations ---
void insertItemList(No** start) {
    No* newNode = (No*)malloc(sizeof(No));
    printf("Item name: ");
    fgets(newNode->dados.nome, 30, stdin);
    newNode->dados.nome[strcspn(newNode->dados.nome, "\n")] = 0;
    printf("Type: ");
    fgets(newNode->dados.tipo, 20, stdin);
    newNode->dados.tipo[strcspn(newNode->dados.tipo, "\n")] = 0;
    printf("Quantity: ");
    scanf("%d", &newNode->dados.quantidade);
    clearBuffer();
    newNode->proximo = *start;
    *start = newNode;
}

void removeItemList(No** start) {
    char name[30];
    printf("Name of the item to remove: ");
    fgets(name, 30, stdin);
    name[strcspn(name, "\n")] = 0;
    No* current = *start, *previous = NULL;
    while (current != NULL && strcmp(current->dados.nome, name) != 0) {
        previous = current;
        current = current->proximo;
    }
    if (current == NULL) {
        printf("Item not found.\n");
        return;
    }
    if (previous == NULL) *start = current->proximo;
    else previous->proximo = current->proximo;
    free(current);
    printf("Item removed.\n");
}

void listItemsList(const No* start) {
    printf("\n--- Items in Linked List ---\n");
    const No* current = start;
    while (current != NULL) {
        printf("Name: %s, Type: %s, Qty: %d\n", current->dados.nome, current->dados.tipo, current->dados.quantidade);
        current = current->proximo;
    }
}

void sequentialSearchList(const No* start) {
    char name[30];
    printf("Name of the item to search: ");
    fgets(name, 30, stdin);
    name[strcspn(name, "\n")] = 0;
    const No* current = start;
    int comparisons = 0;
    while (current != NULL) {
        comparisons++;
        if (strcmp(current->dados.nome, name) == 0) {
            printf("Item found! Comparisons: %d\n", comparisons);
            return;
        }
        current = current->proximo;
    }
    printf("Item not found. Comparisons: %d\n", comparisons);
}

void freeList(No* start) {
    No* current = start;
    while (current != NULL) {
        No* temp = current;
        current = current->proximo;
        free(temp);
    }
}

// --- Utility Function ---
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
