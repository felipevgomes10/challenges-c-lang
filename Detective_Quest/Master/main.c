#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 10

// --- 1. Binary Tree (Map) ---
typedef struct Room {
    char name[50];
    char* clue;
    struct Room* left;
    struct Room* right;
} Room;

// --- 2. Binary Search Tree (Clue Inventory) ---
typedef struct ClueNode {
    char* clue;
    struct ClueNode* left;
    struct ClueNode* right;
} ClueNode;

// --- 3. Hash Table (Suspects) ---
typedef struct HashNode {
    char* clue;
    char* suspect;
    struct HashNode* next;
} HashNode;

HashNode* hashTable[HASH_TABLE_SIZE];

// --- Function Prototypes ---
// Memory Freeing Functions
void freeMap(Room* room);
void freeClueBST(ClueNode* root);
void freeHashTable();

// Map
Room* createRoom(const char* name, const char* clue);
void exploreRooms(Room* room, ClueNode** bstRoot);
// BST
void addClue(ClueNode** root, const char* clue);
void displayClues(ClueNode* root);
int countCluesForSuspect(ClueNode* root, const char* suspect);
// Hash Table
unsigned int hash(const char* key);
void insertIntoHashTable(const char* clue, const char* suspect);
const char* findSuspect(const char* clue);
// Game Logic
void verifyFinalSuspect(ClueNode* bstRoot, const char* accused);
void clearBuffer();


int main() {
    // --- Setup Phase ---
    // 1. Build the Map (Binary Tree)
    Room* map = createRoom("Entrance Hall", NULL);
    map->left = createRoom("Living Room", "A torn business card");
    map->right = createRoom("Dining Room", "An overturned wine glass");
    map->left->left = createRoom("Library", "A book on rare poisons");
    map->left->right = createRoom("Kitchen", "A recently used knife");
    map->right->right = createRoom("Office", "A threatening letter");

    // 2. Setup the Suspects (Hash Table)
    for (int i = 0; i < HASH_TABLE_SIZE; i++) hashTable[i] = NULL;
    insertIntoHashTable("A torn business card", "Mr. Blackwood");
    insertIntoHashTable("An overturned wine glass", "Mrs. Scarlet");
    insertIntoHashTable("A book on rare poisons", "Dr. Orchid");
    insertIntoHashTable("A recently used knife", "The Butler");
    insertIntoHashTable("A threatening letter", "Mr. Blackwood");

    // 3. Initialize Clue Inventory (BST)
    ClueNode* clueInventory = NULL;

    // --- Game Flow ---
    exploreRooms(map, &clueInventory);

    // --- Accusation Phase ---
    printf("\n--- Accusation Phase ---\n");
    printf("Collected Clues:\n");
    displayClues(clueInventory);

    if (clueInventory != NULL) {
        char accused[50];
        printf("\nBased on the evidence, who do you accuse? ");
        fgets(accused, 50, stdin);
        accused[strcspn(accused, "\n")] = 0;
        verifyFinalSuspect(clueInventory, accused);
    } else {
        printf("\nYou found no clues. The mystery remains unsolved.\n");
    }

    // --- Memory Management ---
    printf("\n--- Freeing all allocated memory ---\n");
    freeMap(map);
    freeClueBST(clueInventory);
    freeHashTable();
    printf("Memory freed successfully.\n");

    return 0;
}

// --- Map Functions ---
Room* createRoom(const char* name, const char* clue) {
    Room* newRoom = (Room*)malloc(sizeof(Room));
    strcpy(newRoom->name, name);
    newRoom->left = newRoom->right = NULL;
    if (clue) {
        newRoom->clue = (char*)malloc(strlen(clue) + 1);
        strcpy(newRoom->clue, clue);
    } else {
        newRoom->clue = NULL;
    }
    return newRoom;
}

void exploreRooms(Room* room, ClueNode** bstRoot) {
    char choice;
    while (room != NULL) {
        printf("\n>>> You are in the: %s <<<\n", room->name);
        if (room->clue) {
            printf("You found a clue: '%s'\n", room->clue);
            addClue(bstRoot, room->clue);
            free(room->clue); // Clue collected
            room->clue = NULL;
        }

        if (!room->left && !room->right) {
            printf("This is a dead end.\n");
            break;
        }

        printf("Where to? (l for left, r for right, q to quit): ");
        scanf(" %c", &choice);
        clearBuffer();

        if (choice == 'l') room = room->left;
        else if (choice == 'r') room = room->right;
        else if (choice == 'q') break;
        else printf("Invalid direction.\n");
    }
}

// --- BST Functions ---
void addClue(ClueNode** root, const char* clue) {
    if (*root == NULL) {
        *root = (ClueNode*)malloc(sizeof(ClueNode));
        (*root)->clue = (char*)malloc(strlen(clue) + 1);
        strcpy((*root)->clue, clue);
        (*root)->left = (*root)->right = NULL;
        return;
    }
    if (strcmp(clue, (*root)->clue) < 0) {
        addClue(&(*root)->left, clue);
    } else if (strcmp(clue, (*root)->clue) > 0) {
        addClue(&(*root)->right, clue);
    }
}

void displayClues(ClueNode* root) {
    if (root == NULL) return;
    displayClues(root->left);
    printf("- %s\n", root->clue);
    displayClues(root->right);
}

// --- Hash Table Functions ---
unsigned int hash(const char* key) {
    unsigned int hash = 0;
    while (*key) hash = (hash << 5) + *key++;
    return hash % HASH_TABLE_SIZE;
}

void insertIntoHashTable(const char* clue, const char* suspect) {
    unsigned int index = hash(clue);
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    newNode->clue = (char*)malloc(strlen(clue) + 1);
    strcpy(newNode->clue, clue);
    newNode->suspect = (char*)malloc(strlen(suspect) + 1);
    strcpy(newNode->suspect, suspect);
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

const char* findSuspect(const char* clue) {
    unsigned int index = hash(clue);
    HashNode* current = hashTable[index];
    while (current) {
        if (strcmp(current->clue, clue) == 0) {
            return current->suspect;
        }
        current = current->next;
    }
    return NULL;
}


// --- Game Logic Functions ---
int countCluesForSuspect(ClueNode* root, const char* suspect) {
    if (root == NULL) return 0;
    int count = 0;
    const char* suspectOfClue = findSuspect(root->clue);
    if (suspectOfClue && strcmp(suspectOfClue, suspect) == 0) {
        count = 1;
    }
    return count + countCluesForSuspect(root->left, suspect) + countCluesForSuspect(root->right, suspect);
}

void verifyFinalSuspect(ClueNode* bstRoot, const char* accused) {
    printf("\nChecking evidence against '%s'...\n", accused);
    int evidenceCount = countCluesForSuspect(bstRoot, accused);

    printf("Found %d piece(s) of evidence pointing to %s.\n", evidenceCount, accused);

    if (evidenceCount >= 2) {
        printf("Accusation confirmed! The evidence is overwhelming. You solved the case!\n");
    } else {
        printf("Evidence is insufficient. The suspect might be innocent.\n");
    }
}

// --- Memory Freeing Functions ---
void freeMap(Room* room) {
    if (room == NULL) return;
    freeMap(room->left);
    freeMap(room->right);
    if (room->clue) free(room->clue);
    free(room);
}

void freeClueBST(ClueNode* root) {
    if (root == NULL) return;
    freeClueBST(root->left);
    freeClueBST(root->right);
    free(root->clue);
    free(root);
}

void freeHashTable() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HashNode* current = hashTable[i];
        while (current) {
            HashNode* temp = current;
            current = current->next;
            free(temp->clue);
            free(temp->suspect);
            free(temp);
        }
    }
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
