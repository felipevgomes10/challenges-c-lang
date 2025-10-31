#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUEUE_SIZE 5
#define STACK_SIZE 3

// Struct for a piece
typedef struct {
    char name; // 'I', 'O', 'T', 'L'
    int id;
} Piece;

// Circular Queue for upcoming pieces
typedef struct {
    Piece items[QUEUE_SIZE];
    int start, end, total;
} CircularQueue;

// Stack for reserved pieces
typedef struct {
    Piece items[STACK_SIZE];
    int top;
} LinearStack;

// --- Function Prototypes ---
void initializeQueue(CircularQueue* q);
int isQueueFull(const CircularQueue* q);
int isQueueEmpty(const CircularQueue* q);
void enqueue(CircularQueue* q, Piece p);
Piece dequeue(CircularQueue* q);

void initializeStack(LinearStack* s);
int isStackFull(const LinearStack* s);
int isStackEmpty(const LinearStack* s);
void push(LinearStack* s, Piece p);
Piece pop(LinearStack* s);

Piece generatePiece();
void showState(const CircularQueue* q, const LinearStack* s);

int main() {
    CircularQueue queue;
    LinearStack stack;
    int option;

    srand(time(NULL));
    initializeQueue(&queue);
    initializeStack(&stack);

    // Initially fill the queue
    for (int i = 0; i < QUEUE_SIZE; i++) {
        enqueue(&queue, generatePiece());
    }

    do {
        showState(&queue, &stack);
        printf("\n--- Tetris Stack Menu ---\n");
        printf("1. Play piece\n");
        printf("2. Reserve piece\n");
        printf("3. Use reserved piece\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1: // Play piece
                if (!isQueueEmpty(&queue)) {
                    Piece played = dequeue(&queue);
                    printf("Piece '%c' (ID: %d) played.\n", played.name, played.id);
                    enqueue(&queue, generatePiece()); // Add a new piece
                } else {
                    printf("Queue is empty!\n");
                }
                break;
            case 2: // Reserve piece
                if (!isQueueEmpty(&queue) && !isStackFull(&stack)) {
                    Piece reserved = dequeue(&queue);
                    push(&stack, reserved);
                    printf("Piece '%c' (ID: %d) reserved.\n", reserved.name, reserved.id);
                    enqueue(&queue, generatePiece()); // Add a new piece
                } else {
                    if(isQueueEmpty(&queue)) printf("Queue is empty!\n");
                    if(isStackFull(&stack)) printf("Reserve stack is full!\n");
                }
                break;
            case 3: // Use reserved piece
                if (!isStackEmpty(&stack)) {
                    Piece used = pop(&stack);
                    printf("Piece '%c' (ID: %d) from reserve was used.\n", used.name, used.id);
                } else {
                    printf("Reserve stack is empty!\n");
                }
                break;
            case 4:
                printf("Exiting the game.\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (option != 4);

    return 0;
}

// --- Queue Functions ---
void initializeQueue(CircularQueue* q) { q->start = q->end = q->total = 0; }
int isQueueFull(const CircularQueue* q) { return q->total == QUEUE_SIZE; }
int isQueueEmpty(const CircularQueue* q) { return q->total == 0; }

void enqueue(CircularQueue* q, Piece p) {
    if (isQueueFull(q)) return;
    q->items[q->end] = p;
    q->end = (q->end + 1) % QUEUE_SIZE;
    q->total++;
}

Piece dequeue(CircularQueue* q) {
    Piece p = q->items[q->start];
    q->start = (q->start + 1) % QUEUE_SIZE;
    q->total--;
    return p;
}

// --- Stack Functions ---
void initializeStack(LinearStack* s) { s->top = -1; }
int isStackFull(const LinearStack* s) { return s->top == STACK_SIZE - 1; }
int isStackEmpty(const LinearStack* s) { return s->top == -1; }

void push(LinearStack* s, Piece p) {
    if (isStackFull(s)) return;
    s->items[++(s->top)] = p;
}

Piece pop(LinearStack* s) {
    return s->items[(s->top)--];
}

// --- Utility Functions ---
Piece generatePiece() {
    static int nextId = 1;
    Piece newPiece;
    char types[] = "IOTL";
    newPiece.name = types[rand() % 4];
    newPiece.id = nextId++;
    return newPiece;
}

void showState(const CircularQueue* q, const LinearStack* s) {
    printf("\n\n--- Current Game State ---\n");
    // Display Queue
    printf("Piece queue: ");
    if (isQueueEmpty(q)) {
        printf("[Empty]");
    } else {
        int i = q->start;
        for (int count = 0; count < q->total; count++) {
            printf("[%c,ID:%d] ", q->items[i].name, q->items[i].id);
            i = (i + 1) % QUEUE_SIZE;
        }
    }
    // Display Stack
    printf("\nReserve stack: ");
    if (isStackEmpty(s)) {
        printf("[Empty]");
    } else {
        for (int i = 0; i <= s->top; i++) {
            printf("[%c,ID:%d] ", s->items[i].name, s->items[i].id);
        }
    }
    printf("\n");
}
