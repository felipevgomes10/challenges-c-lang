#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTS 20

// Struct for an escape tower component
typedef struct Componente {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// --- Function Prototypes ---
void registerComponents(Componente components[], int* count);
void displayComponents(const Componente components[], int count);
void bubbleSortNome(Componente components[], int count);
void insertionSortTipo(Componente components[], int count);
void selectionSortPrioridade(Componente components[], int count);
void buscaBinariaPorNome(const Componente components[], int count);
void clearBuffer();

int main() {
    Componente components[MAX_COMPONENTS];
    int componentCount = 0;
    int option;

    do {
        printf("\n--- Escape Tower Component Manager ---\n");
        printf("1. Register Components\n");
        printf("2. Sort by Name (Bubble Sort)\n");
        printf("3. Sort by Type (Insertion Sort)\n");
        printf("4. Sort by Priority (Selection Sort)\n");
        printf("5. Find Component by Name (Binary Search)\n");
        printf("6. Display All Components\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);
        clearBuffer();

        switch (option) {
            case 1:
                registerComponents(components, &componentCount);
                break;
            case 2:
                bubbleSortNome(components, componentCount);
                displayComponents(components, componentCount);
                break;
            case 3:
                insertionSortTipo(components, componentCount);
                displayComponents(components, componentCount);
                break;
            case 4:
                selectionSortPrioridade(components, componentCount);
                displayComponents(components, componentCount);
                break;
            case 5:
                printf("Note: Components must be sorted by name first.\n");
                buscaBinariaPorNome(components, componentCount);
                break;
            case 6:
                displayComponents(components, componentCount);
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 0);

    return 0;
}

// Function to register new components
void registerComponents(Componente components[], int* count) {
    if (*count >= MAX_COMPONENTS) {
        printf("Maximum number of components reached.\n");
        return;
    }
    printf("\n--- Register New Component ---\n");
    printf("Component Name: ");
    fgets(components[*count].nome, 30, stdin);
    components[*count].nome[strcspn(components[*count].nome, "\n")] = 0;

    printf("Component Type: ");
    fgets(components[*count].tipo, 20, stdin);
    components[*count].tipo[strcspn(components[*count].tipo, "\n")] = 0;

    printf("Priority (1-10): ");
    scanf("%d", &components[*count].prioridade);
    clearBuffer();

    (*count)++;
    printf("Component registered successfully.\n");
}

// Function to display all components
void displayComponents(const Componente components[], int count) {
    if (count == 0) {
        printf("No components registered yet.\n");
        return;
    }
    printf("\n--- List of Registered Components ---\n");
    printf("%-20s | %-15s | %s\n", "Name", "Type", "Priority");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-20s | %-15s | %d\n", components[i].nome, components[i].tipo, components[i].prioridade);
    }
}

// --- Sorting and Searching Functions with Performance Analysis ---

void bubbleSortNome(Componente components[], int count) {
    long long comparisons = 0;
    clock_t start = clock();

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            comparisons++;
            if (strcmp(components[j].nome, components[j + 1].nome) > 0) {
                Componente temp = components[j];
                components[j] = components[j + 1];
                components[j + 1] = temp;
            }
        }
    }
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n--- Bubble Sort (by Name) Performance ---\n");
    printf("Comparisons: %lld\n", comparisons);
    printf("Execution Time: %f seconds\n", time_spent);
}

void insertionSortTipo(Componente components[], int count) {
    long long comparisons = 0;
    clock_t start = clock();

    for (int i = 1; i < count; i++) {
        Componente key = components[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (strcmp(components[j].tipo, key.tipo) > 0) {
                components[j + 1] = components[j];
                j = j - 1;
            } else {
                break;
            }
        }
        components[j + 1] = key;
    }
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n--- Insertion Sort (by Type) Performance ---\n");
    printf("Comparisons: %lld\n", comparisons);
    printf("Execution Time: %f seconds\n", time_spent);
}

void selectionSortPrioridade(Componente components[], int count) {
    long long comparisons = 0;
    clock_t start = clock();

    for (int i = 0; i < count - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < count; j++) {
            comparisons++;
            if (components[j].prioridade < components[min_idx].prioridade) {
                min_idx = j;
            }
        }
        Componente temp = components[min_idx];
        components[min_idx] = components[i];
        components[i] = temp;
    }
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n--- Selection Sort (by Priority) Performance ---\n");
    printf("Comparisons: %lld\n", comparisons);
    printf("Execution Time: %f seconds\n", time_spent);
}

void buscaBinariaPorNome(const Componente components[], int count) {
    char key[30];
    printf("Enter the component name to find: ");
    fgets(key, 30, stdin);
    key[strcspn(key, "\n")] = 0;

    int low = 0, high = count - 1, mid;
    int comparisons = 0;
    int found = 0;

    while (low <= high) {
        mid = low + (high - low) / 2;
        comparisons++;
        int cmp = strcmp(components[mid].nome, key);
        if (cmp == 0) {
            printf("\n--- Component Found ---\n");
            printf("Name: %s, Type: %s, Priority: %d\n", components[mid].nome, components[mid].tipo, components[mid].prioridade);
            found = 1;
            break;
        }
        if (cmp < 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (!found) {
        printf("Component '%s' not found.\n", key);
    }
    printf("Binary Search Comparisons: %d\n", comparisons);
}

// Function to clear the input buffer
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
