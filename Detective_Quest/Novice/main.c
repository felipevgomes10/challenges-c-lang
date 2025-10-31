#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for a room (node in the binary tree)
typedef struct Room {
    char name[50];
    struct Room* left;
    struct Room* right;
} Room;

// --- Function Prototypes ---
Room* createRoom(const char* name);
void exploreRooms(Room* currentRoom);
void freeMap(Room* currentRoom);
void clearBuffer();

int main() {
    // --- Manual Map Creation ---
    Room* root = createRoom("Entrance Hall");
    root->left = createRoom("Living Room");
    root->right = createRoom("Dining Room");

    root->left->left = createRoom("Library");
    root->left->right = createRoom("Kitchen");

    root->right->left = createRoom("Guest Room");
    root->right->right = createRoom("Office");

    // Start the exploration
    exploreRooms(root);

    // Free the allocated memory
    freeMap(root);

    return 0;
}

// Function to create a new room (node)
Room* createRoom(const char* name) {
    Room* newRoom = (Room*)malloc(sizeof(Room));
    if (newRoom == NULL) {
        printf("Error allocating memory for the room.\n");
        exit(1);
    }
    strcpy(newRoom->name, name);
    newRoom->left = NULL;
    newRoom->right = NULL;
    return newRoom;
}

// Function for interactive exploration
void exploreRooms(Room* currentRoom) {
    char choice;

    while (currentRoom != NULL) {
        printf("\nYou are in: %s\n", currentRoom->name);

        // Check for possible paths
        if (currentRoom->left == NULL && currentRoom->right == NULL) {
            printf("This is a dead end. End of exploration.\n");
            break;
        }

        printf("Where do you want to go?\n");
        if (currentRoom->left != NULL) {
            printf("  (l) to the Left (%s)\n", currentRoom->left->name);
        }
        if (currentRoom->right != NULL) {
            printf("  (r) to the Right (%s)\n", currentRoom->right->name);
        }
        printf("  (q) to Quit\n");
        printf("Choice: ");
        scanf(" %c", &choice);
        clearBuffer();

        if (choice == 'l' || choice == 'L') {
            if (currentRoom->left != NULL) {
                currentRoom = currentRoom->left;
            } else {
                printf("There is no path to the left.\n");
            }
        } else if (choice == 'r' || choice == 'R') {
            if (currentRoom->right != NULL) {
                currentRoom = currentRoom->right;
            } else {
                printf("There is no path to the right.\n");
            }
        } else if (choice == 'q' || choice == 'Q') {
            printf("You have decided to leave the mansion.\n");
            break;
        } else {
            printf("Invalid option.\n");
        }
    }
}

// Function to free the memory of the map (tree)
void freeMap(Room* currentRoom) {
    if (currentRoom == NULL) {
        return;
    }
    freeMap(currentRoom->left);
    freeMap(currentRoom->right);
    free(currentRoom);
}

// Function to clear the input buffer
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
