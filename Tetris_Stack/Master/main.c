#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUEUE_SIZE 5
#define STACK_SIZE 3

// Struct for a piece
typedef struct {
    char name;
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
Piece peekQueue(const CircularQueue* q);

void initializeStack(LinearStack* s);
int isStackFull(const LinearStack* s);
int isStackEmpty(const LinearStack* s);
void pushStack(LinearStack* s, Piece piece);
Piece popStack(LinearStack* s);
Piece peekStack(const LinearStack* s);

Piece generatePiece();
void showState(const CircularQueue* q, const LinearStack* s);
void swapCurrentPiece(CircularQueue* q, LinearStack* s);
void multipleSwap(CircularQueue* q, LinearStack* s);

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
        printf("\n--- Tetris Stack: Master Menu ---\n");
        printf("1. Play piece\n");
        printf("2. Reserve piece\n");
        printf("3. Use reserved piece\n");
        printf("4. Swap current piece with reserved\n");
        printf("5. Multiple swap (3 pieces)\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1: // Play piece
                if (!isQueueEmpty(&queue)) {
                    Piece played = dequeue(&queue);
                    printf("Piece '%c' (ID: %d) played.\n", played.name, played.id);
                    enqueue(&queue, generatePiece());
                } else {
                    printf("Queue is empty!\n");
                }
                break;
            case 2: // Reserve piece
                if (!isQueueEmpty(&queue) && !isStackFull(&stack)) {
                    pushStack(&stack, dequeue(&queue));
                    enqueue(&queue, generatePiece());
                } else {
                    printf("Cannot reserve. Queue empty or Stack full.\n");
                }
                break;
            case 3: // Use reserved piece
                if (!isStackEmpty(&stack)) {
                    Piece used = popStack(&stack);
                    printf("Used reserved piece '%c' (ID: %d).\n", used.name, used.id);
                } else {
                    printf("Reserve stack is empty!\n");
                }
                break;
            case 4: // Swap current piece
                swapCurrentPiece(&queue, &stack);
                break;
            case 5: // Multiple swap
                multipleSwap(&queue, &stack);
                break;
            case 0:
                printf("Exiting game.\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (option != 0);

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
Piece peekQueue(const CircularQueue* q) { return q->items[q->start]; }


// --- Stack Functions ---
void initializeStack(LinearStack* s) { s->top = -1; }
int isStackFull(const LinearStack* s) { return s->top == STACK_SIZE - 1; }
int isStackEmpty(const LinearStack* s) { return s->top == -1; }
void pushStack(LinearStack* s, Piece piece) {
    if (isStackFull(s)) return;
    s->items[++(s->top)] = piece;
}
Piece popStack(LinearStack* s) { return s->items[(s->top)--]; }
Piece peekStack(const LinearStack* s) { return s->items[s->top]; }


// --- Game Logic Functions ---
void swapCurrentPiece(CircularQueue* q, LinearStack* s) {
    if (isQueueEmpty(q) || isStackEmpty(s)) {
        printf("Both queue and stack must have at least one piece to swap.\n");
        return;
    }
    Piece queuePiece = dequeue(q);
    Piece stackPiece = popStack(s);

    // Create a temporary queue to re-insert the swapped piece at the front
    CircularQueue tempQueue;
    initializeQueue(&tempQueue);
    enqueue(&tempQueue, stackPiece);
    while(!isQueueEmpty(q)){
        enqueue(&tempQueue, dequeue(q));
    }
    *q = tempQueue;

    pushStack(s, queuePiece);
    printf("Swapped front of queue with top of stack.\n");
}

void multipleSwap(CircularQueue* q, LinearStack* s) {
    if (q->total < 3 || s->top + 1 < 3) {
        printf("Both queue and stack must have at least 3 pieces for multiple swap.\n");
        return;
    }

    // Simple swap since order in stack doesn't matter beyond LIFO
    Piece temp;
    // Swap 1
    temp = q->items[q->start];
    q->items[q->start] = s->items[s->top];
    s->items[s->top] = temp;
    // Swap 2
    temp = q->items[(q->start + 1) % QUEUE_SIZE];
    q->items[(q->start + 1) % QUEUE_SIZE] = s->items[s->top - 1];
    s->items[s->top - 1] = temp;
    // Swap 3
    temp = q->items[(q->start + 2) % QUEUE_SIZE];
    q->items[(q->start + 2) % QUEUE_SIZE] = s->items[s->top - 2];
    s->items[s->top - 2] = temp;

    printf("Performed a multiple swap of 3 pieces.\n");
}

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
    printf("Queue (%d/%d): ", q->total, QUEUE_SIZE);
    if (isQueueEmpty(q)) {
        printf("[Empty]");
    } else {
        int i = q->start;
        for (int count = 0; count < q->total; count++) {
            printf("[%c:%d] ", q->items[i].name, q->items[i].id);
            i = (i + 1) % QUEUE_SIZE;
        }
    }
    printf("\nStack (%d/%d): ", s->top + 1, STACK_SIZE);
    if (isStackEmpty(s)) {
        printf("[Empty]");
    } else {
        for (int i = 0; i <= s->top; i++) {
            printf("[%c:%d] ", s->items[i].name, s->items[i].id);
        }
    }
    printf("\n");
}
