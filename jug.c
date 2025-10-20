#include <stdio.h>
#include <stdlib.h>
#define MAX 11

typedef struct {
    int a, b, c;
} State;

typedef struct Node {
    State state;
    struct Node *next;
} Node;

Node *front = NULL, *rear = NULL;

void enqueue(State s) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->state = s;
    newNode->next = NULL;

    if (rear == NULL)
        front = rear = newNode;
    else {
        rear->next = newNode;
        rear = newNode;
    }
}

State dequeue() {
    Node *temp = front;
    State s = temp->state;
    front = front->next;
    if (front == NULL)
        rear = NULL;
    free(temp);
    return s;
}

int isEmpty() { return front == NULL; }

// MAX = 11
int visited[MAX][MAX][MAX];

void printState(State s) { printf("(%d, %d, %d)\n", s.a, s.b, s.c); }

State pour(State s, int from, int to, int capFrom, int capTo) {
    int *jug[] = {&s.a, &s.b, &s.c};
    int amount = jug[from][0];
    int space = capTo - jug[to][0];
    int pourAmt = (amount < space) ? amount : space;
    jug[from][0] -= pourAmt;
    jug[to][0] += pourAmt;
    return s;
}

int main() {
    int cap[3] = {10, 7, 4};
    State start = {0, 7, 4};
    State curr;

    enqueue(start);
    visited[start.a][start.b][start.c] = 1;

    printf("BFS order of states:\n");

    while (!isEmpty()) {
        curr = dequeue();
        printState(curr);

        if (curr.b == 2 || curr.c == 2) {
            printf("\nGoal reached at state: ");
            printState(curr);
            return 0;
        }

        int i, j;

        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (i != j) {
                    State next = pour(curr, i, j, cap[i], cap[j]);
                    if (!visited[next.a][next.b][next.c]) {
                        visited[next.a][next.b][next.c] = 1;
                        enqueue(next);
                    }
                }
            }
        }
    }

    printf("Goal state not reachable.\n");
    return 0;
}
