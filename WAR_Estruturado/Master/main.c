#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct for a territory
typedef struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- Function Prototypes ---
void atribuirMissao(char** destino, char* missoes[], int totalMissoes);
int verificarMissao(const char* missao, const Territorio* mapa, int tamanho, const char* corJogador);
void atacar(Territorio* atacante, Territorio* defensor);
void exibirMapa(const Territorio* mapa, int tamanho);
void liberarMemoria(Territorio* mapa, char* missao, int tamanho);

int main() {
    // --- Game Setup ---
    srand(time(NULL));
    int numTerritorios = 6; // Example size
    Territorio* mapa = (Territorio*)calloc(numTerritorios, sizeof(Territorio));
    char* missaoJogador = NULL;

    // Predefined missions vector
    char* missoes[] = {
        "Conquer 3 territories",
        "Eliminate all red troops",
        "Conquer North America", // Placeholder
        "Hold 2 continents",     // Placeholder
        "Destroy the blue army"
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    // Initial map setup (example)
    strcpy(mapa[0].nome, "Alaska"); strcpy(mapa[0].cor, "blue"); mapa[0].tropas = 3;
    strcpy(mapa[1].nome, "Alberta"); strcpy(mapa[1].cor, "blue"); mapa[1].tropas = 5;
    strcpy(mapa[2].nome, "Greenland"); strcpy(mapa[2].cor, "red"); mapa[2].tropas = 2;
    strcpy(mapa[3].nome, "Quebec"); strcpy(mapa[3].cor, "red"); mapa[3].tropas = 4;
    strcpy(mapa[4].nome, "Ontario"); strcpy(mapa[4].cor, "green"); mapa[4].tropas = 6;
    strcpy(mapa[5].nome, "New York"); strcpy(mapa[5].cor, "green"); mapa[5].tropas = 1;


    // --- Mission Assignment ---
    atribuirMissao(&missaoJogador, missoes, totalMissoes);
    printf("--- Your Mission ---\n%s\n\n", missaoJogador);

    // --- Game Loop (Simplified) ---
    int turno = 0;
    const char* jogadorAtual = "blue"; // Example: blue player's turn
    int vitoria = 0;

    while (turno < 5 && !vitoria) {
        printf("--- Turn %d (%s player) ---\n", turno + 1, jogadorAtual);
        exibirMapa(mapa, numTerritorios);

        // Simple attack simulation for demonstration
        printf("\nSimulating an attack...\n");
        int atacanteIdx = 0; // blue's Alaska
        int defensorIdx = 2; // red's Greenland
        if (strcmp(mapa[atacanteIdx].cor, mapa[defensorIdx].cor) != 0) {
            atacar(&mapa[atacanteIdx], &mapa[defensorIdx]);
        }

        // --- Victory Check ---
        if (verificarMissao(missaoJogador, mapa, numTerritorios, jogadorAtual)) {
            printf("\n--- Mission Accomplished! ---\n");
            printf("Player %s has won the game!\n", jogadorAtual);
            vitoria = 1;
        } else {
            printf("\nMission not yet accomplished. Continuing game...\n\n");
        }
        turno++;
    }

    if (!vitoria) {
        printf("\n--- Game Over ---\nNo player won within the turn limit.\n");
    }

    // --- Memory Management ---
    liberarMemoria(mapa, missaoJogador, numTerritorios);

    return 0;
}

// Assigns a random mission to the player's destination pointer
void atribuirMissao(char** destino, char* missoes[], int totalMissoes) {
    int indiceMissao = rand() % totalMissoes;
    // Allocate memory for the mission string
    *destino = (char*)malloc(strlen(missoes[indiceMissao]) + 1);
    if (*destino == NULL) {
        printf("Failed to allocate memory for mission.\n");
        exit(1);
    }
    // Copy the mission
    strcpy(*destino, missoes[indiceMissao]);
}

// Checks if the player has completed their mission
int verificarMissao(const char* missao, const Territorio* mapa, int tamanho, const char* corJogador) {
    // Example logic for two missions
    if (strcmp(missao, "Conquer 3 territories") == 0) {
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                count++;
            }
        }
        return count >= 3;
    }
    if (strcmp(missao, "Eliminate all red troops") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "red") == 0) {
                return 0; // Red troops still exist
            }
        }
        return 1; // No red troops found
    }
    // Other missions would be checked here
    return 0; // Default: mission not complete
}

// Simulates an attack between two territories
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("Attacking %s from %s!\n", defensor->nome, atacante->nome);
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    if (dadoAtacante > dadoDefensor) {
        printf("Attacker wins! %s is conquered.\n", defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = 1; // Simplified outcome
    } else {
        printf("Defender holds! Attacker loses one troop.\n");
        if(atacante->tropas > 1) {
            atacante->tropas--;
        }
    }
}

// Displays the current state of the map
void exibirMapa(const Territorio* mapa, int tamanho) {
    printf("--- Current Map State ---\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%s (Color: %s, Troops: %d)\n", mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Frees all dynamically allocated memory
void liberarMemoria(Territorio* mapa, char* missao, int tamanho) {
    if (mapa != NULL) {
        free(mapa);
    }
    if (missao != NULL) {
        free(missao);
    }
    printf("\nAll dynamic memory has been freed.\n");
}
