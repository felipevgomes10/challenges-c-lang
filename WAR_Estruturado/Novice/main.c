#include <stdio.h>
#include <string.h>

// Struct definition for a territory
struct Territorio {
    char nome[30];
    char cor[10]; // Color of the army
    int tropas;    // Number of troops
};

int main() {
    // Static array (vector) to store 5 territories
    struct Territorio territorios[5];
    int i;

    // --- Territory Registration ---
    printf("--- Register 5 Territories ---\n");
    // For loop to manage the registration of the 5 territories
    for (i = 0; i < 5; i++) {
        printf("\n--- Territory %d ---\n", i + 1);

        // Prompt for the territory's name
        printf("Enter the territory's name: ");
        scanf("%s", territorios[i].nome);

        // Prompt for the army's color
        printf("Enter the army's color: ");
        scanf("%s", territorios[i].cor);

        // Prompt for the number of troops
        printf("Enter the number of troops: ");
        scanf("%d", &territorios[i].tropas);
    }

    // --- Data Display ---
    printf("\n--- List of Registered Territories ---\n");
    // For loop to display the registered territories
    for (i = 0; i < 5; i++) {
        printf("\n--- Territory %d ---\n", i + 1);
        printf("Name: %s\n", territorios[i].nome);
        printf("Army's Color: %s\n", territorios[i].cor);
        printf("Number of Troops: %d\n", territorios[i].tropas);
    }

    return 0;
}
