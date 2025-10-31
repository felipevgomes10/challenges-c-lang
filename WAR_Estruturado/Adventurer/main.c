#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct definition for a territory
typedef struct Territorio {
    char nome[30];
    char cor[10]; // Color of the army
    int tropas;    // Number of troops
} Territorio;

// --- Function Prototypes ---
void registrarTerritorios(Territorio* territorios, int n);
void exibirTerritorios(const Territorio* territorios, int n);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* territorios);

int main() {
    int numTerritorios;
    int atacanteIndex, defensorIndex;
    Territorio* territorios = NULL;

    // Use srand to ensure true randomness
    srand(time(NULL));

    // --- Dynamic Memory Allocation ---
    printf("Enter the number of territories to create: ");
    scanf("%d", &numTerritorios);

    // Allocate memory for the territories using calloc
    territorios = (Territorio*)calloc(numTerritorios, sizeof(Territorio));
    if (territorios == NULL) {
        printf("Error allocating memory!\n");
        return 1;
    }

    // --- Territory Registration ---
    registrarTerritorios(territorios, numTerritorios);

    // --- Data Display ---
    exibirTerritorios(territorios, numTerritorios);

    // --- Attack Simulation ---
    printf("\n--- Attack Simulation ---\n");
    printf("Select the attacking territory (by index, 1 to %d): ", numTerritorios);
    scanf("%d", &atacanteIndex);
    printf("Select the defending territory (by index, 1 to %d): ", numTerritorios);
    scanf("%d", &defensorIndex);

    // Adjust indices to be 0-based
    atacanteIndex--;
    defensorIndex--;

    // Validate the indices
    if (atacanteIndex < 0 || atacanteIndex >= numTerritorios ||
        defensorIndex < 0 || defensorIndex >= numTerritorios) {
        printf("Invalid territory selection.\n");
    } else {
        // Use pointers to refer to the territories
        Territorio* atacante = &territorios[atacanteIndex];
        Territorio* defensor = &territorios[defensorIndex];

        // Validate that a player cannot attack their own territory
        if (strcmp(atacante->cor, defensor->cor) == 0) {
            printf("A player cannot attack a territory they already own.\n");
        } else {
            atacar(atacante, defensor);
        }
    }

    // --- Post-Attack Display ---
    printf("\n--- Updated Territory Data ---\n");
    exibirTerritorios(territorios, numTerritorios);

    // --- Memory Management ---
    liberarMemoria(territorios);

    return 0;
}

// Function to register territories
void registrarTerritorios(Territorio* territories, int n) {
    printf("\n--- Register %d Territories ---\n", n);
    for (int i = 0; i < n; i++) {
        printf("\n--- Territory %d ---\n", i + 1);
        printf("Enter the territory's name: ");
        scanf("%s", (territories + i)->nome);
        printf("Enter the army's color: ");
        scanf("%s", (territories + i)->cor);
        printf("Enter the number of troops: ");
        scanf("%d", &(territories + i)->tropas);
    }
}

// Function to display territories
void exibirTerritorios(const Territorio* territories, int n) {
    printf("\n--- List of Territories ---\n");
    for (int i = 0; i < n; i++) {
        printf("\n--- Territory %d ---\n", i + 1);
        printf("Name: %s\n", (territories + i)->nome);
        printf("Army's Color: %s\n", (territories + i)->cor);
        printf("Number of Troops: %d\n", (territories + i)->tropas);
    }
}

// Function to simulate an attack between two territories
void atacar(Territorio* attacker, Territorio* defender) {
    // Simulate a dice roll (1-6) for both attacker and defender
    int attackerRoll = rand() % 6 + 1;
    int defenderRoll = rand() % 6 + 1;

    printf("\n--- Attack Result ---\n");
    printf("Attacker's Roll: %d\n", attackerRoll);
    printf("Defender's Roll: %d\n", defenderRoll);

    // Check the result of the attack
    if (attackerRoll > defenderRoll) {
        // Attacker wins
        printf("Attacker wins! The defending territory is conquered.\n");
        // Change the owner of the defending territory
        strcpy(defender->cor, attacker->cor);
        // Update the number of troops in the defending territory
        defender->tropas = attacker->tropas / 2;
    } else {
        // Attacker loses
        printf("Attacker loses! The attacking territory loses one troop.\n");
        // Decrease the attacker's troops by one
        attacker->tropas--;
    }
}

// Function to free the dynamically allocated memory
void liberarMemoria(Territorio* territories) {
    if (territories != NULL) {
        free(territories);
        printf("\nMemory has been freed.\n");
    }
}
