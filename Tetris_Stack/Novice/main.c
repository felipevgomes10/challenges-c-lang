#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUEUE_SIZE 5

// Struct definition for a piece
typedef struct {
    char name; // 'I', 'O', 'T', 'L'
    int id;
} Piece;

// Circular queue structure
typedef struct {
    Piece items[QUEUE_SIZE];
    int start;
    int end;
    int total;
} CircularQueue;

// --- Function Prototypes ---
void initializeQueue(CircularQueue* q);
int isQueueFull(const CircularQueue* q);
int isQueueEmpty(const CircularQueue* q);
Piece generatePiece();
void enqueue(CircularQueue* q);
void dequeue(CircularQueue* q);
void showQueue(const CircularQueue* q);

int main() {
    CircularQueue pieceQueue;
    int option;
    int nextId = 1; // To generate unique IDs

    srand(time(NULL));
    initializeQueue(&pieceQueue);

    // Initial fill of the queue
    for(int i = 0; i < QUEUE_SIZE; i++) {
        Piece newPiece = {' ', nextId++};
        char types[] = "IOTL";
        newPiece.name = types[rand() % 4];
        pieceQueue.items[pieceQueue.end] = newPiece;
        pieceQueue.end = (pieceQueue.end + 1) % QUEUE_SIZE;
        pieceQueue.total++;
    }

    do {
        showQueue(&pieceQueue);
        printf("\n--- Tetris Stack Menu ---\n");
        printf("1. Play piece\n");
        printf("2. Insert new piece\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                dequeue(&pieceQueue);
                break;
            case 2:
                enqueue(&pieceQueue);
                break;
            case 3:
                printf("Exiting the game.\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (option != 3);

    return 0;
}

// Initialize the queue
void initializeQueue(CircularQueue* q) {
    q->start = 0;
    q->end = 0;
    q->total = 0;
}

// Check if the queue is full
int isQueueFull(const CircularQueue* q) {
    return q->total == QUEUE_SIZE;
}

// Check if the queue is empty
int isQueueEmpty(const CircularQueue* q) {
    return q->total == 0;
}

// Generate a new piece
Piece generatePiece() {
    static int nextId = 1;
    Piece newPiece;
    char types[] = "IOTL";
    newPiece.name = types[rand() % 4];
    newPiece.id = nextId++;
    return newPiece;
}

// Enqueue a new piece
void enqueue(CircularQueue* q) {
    if (isQueueFull(q)) {
        printf("The piece queue is full!\n");
        return;
    }
    Piece newPiece = generatePiece();
    q->items[q->end] = newPiece;
    q->end = (q->end + 1) % QUEUE_SIZE;
    q->total++;
    printf("New piece '%c' (ID: %d) inserted.\n", newPiece.name, newPiece.id);
}

// Dequeue a piece
void dequeue(CircularQueue* q) {
    if (isQueueEmpty(q)) {
        printf("The piece queue is empty!\n");
        return;
    }
    Piece playedPiece = q->items[q->start];
    q->start = (q->start + 1) % QUEUE_SIZE;
    q->total--;
    printf("Piece '%c' (ID: %d) was played.\n", playedPiece.name, playedPiece.id);
}

// Display the current state of the queue
void showQueue(const CircularQueue* q) {
    if (isQueueEmpty(q)) {
        printf("\nNext pieces queue: [Empty]\n");
        return;
    }
    printf("\n--- Next Pieces Queue ---\n");
    int i = q->start;
    for (int count = 0; count < q->total; count++) {
        printf("[%c, ID:%d] ", q->items[i].name, q->items[i].id);
        i = (i + 1) % QUEUE_SIZE;
    }
    printf("\n");
}
