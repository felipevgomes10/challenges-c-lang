#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Struct for the Map (Binary Tree) ---
typedef struct Room {
    char name[50];
    char* clue; // Clue in the room
    struct Room* left;
    struct Room* right;
} Room;

// --- Struct for the Clue Inventory (BST) ---
typedef struct ClueNode {
    char* clue;
    struct ClueNode* left;
    struct ClueNode* right;
} ClueNode;

// --- Function Prototypes ---
// Map functions
Room* createRoom(const char* name, const char* clue);
void exploreRoomsWithClues(Room* currentRoom, ClueNode** cluesRoot);
void freeMap(Room* room);

// BST functions
ClueNode* createClueNode(const char* clue);
void insertClue(ClueNode** root, const char* clue);
void displayClues(ClueNode* root);
void freeClues(ClueNode* root);

// Utility
void clearBuffer();

int main() {
    // --- Manual Map Creation with Clues ---
    Room* map = createRoom("Entrance Hall", NULL);
    map->left = createRoom("Living Room", "A receipt from a tool store dated yesterday.");
    map->right = createRoom("Dining Room", "A broken plate with a strange monogram.");
    map->left->left = createRoom("Library", "A book on poisons with a marked page.");
    map->left->right = createRoom("Kitchen", NULL);
    map->right->left = createRoom("Guest Room", "A half-unpacked suitcase with clothes that are not the victim's.");
    map->right->right = createRoom("Office", "A threatening letter in the desk drawer.");

    // Root of the BST for clues
    ClueNode* clueInventory = NULL;

    // Start exploration and clue collection
    exploreRoomsWithClues(map, &clueInventory);

    // Final Report: Display collected clues
    printf("\n\n--- Final Report: Collected Clues (in order) ---\n");
    displayClues(clueInventory);
    if (clueInventory == NULL) {
        printf("No clues were collected.\n");
    }

    // Free all allocated memory
    freeMap(map);
    freeClues(clueInventory);

    return 0;
}

// --- Map Function Implementations ---
Room* createRoom(const char* name, const char* clue) {
    Room* newRoom = (Room*)malloc(sizeof(Room));
    strcpy(newRoom->name, name);
    newRoom->left = newRoom->right = NULL;
    if (clue != NULL) {
        newRoom->clue = (char*)malloc(strlen(clue) + 1);
        strcpy(newRoom->clue, clue);
    } else {
        newRoom->clue = NULL;
    }
    return newRoom;
}

void exploreRoomsWithClues(Room* currentRoom, ClueNode** cluesRoot) {
    char choice;
    while (currentRoom != NULL) {
        printf("\nYou are in: %s\n", currentRoom->name);

        // Collect clue if it exists
        if (currentRoom->clue != NULL) {
            printf("You found a clue: \"%s\"\n", currentRoom->clue);
            insertClue(cluesRoot, currentRoom->clue);
            // Free the clue from the room to avoid re-adding it
            free(currentRoom->clue);
            currentRoom->clue = NULL;
        }

        if (currentRoom->left == NULL && currentRoom->right == NULL) {
            printf("This is a dead end.\n");
            break;
        }

        printf("Where do you want to go? (l/r/q): ");
        scanf(" %c", &choice);
        clearBuffer();

        if (choice == 'l' && currentRoom->left) currentRoom = currentRoom->left;
        else if (choice == 'r' && currentRoom->right) currentRoom = currentRoom->right;
        else if (choice == 'q') break;
        else printf("Invalid path.\n");
    }
    printf("\nYou have decided to stop the exploration.\n");
}

void freeMap(Room* room) {
    if (room == NULL) return;
    freeMap(room->left);
    freeMap(room->right);
    if (room->clue != NULL) free(room->clue);
    free(room);
}

// --- BST Function Implementations ---
ClueNode* createClueNode(const char* clue) {
    ClueNode* newNode = (ClueNode*)malloc(sizeof(ClueNode));
    newNode->clue = (char*)malloc(strlen(clue) + 1);
    strcpy(newNode->clue, clue);
    newNode->left = newNode->right = NULL;
    return newNode;
}

void insertClue(ClueNode** root, const char* clue) {
    if (*root == NULL) {
        *root = createClueNode(clue);
        printf(" -> Clue added to inventory.\n");
        return;
    }
    int cmp = strcmp(clue, (*root)->clue);
    if (cmp < 0) {
        insertClue(&(*root)->left, clue);
    } else if (cmp > 0) {
        insertClue(&(*root)->right, clue);
    }
    // If cmp == 0, the clue is already in the BST, do nothing.
}

// In-order traversal to display clues alphabetically
void displayClues(ClueNode* root) {
    if (root == NULL) return;
    displayClues(root->left);
    printf("- %s\n", root->clue);
    displayClues(root->right);
}

void freeClues(ClueNode* root) {
    if (root == NULL) return;
    freeClues(root->left);
    freeClues(root->right);
    free(root->clue);
    free(root);
}

// --- Utility Function ---
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
