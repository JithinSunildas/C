#include <stdio.h>

typedef struct {
    int size;
    int value[100];
    int head;
    int tail;
} Buf;

int next(int i, int size) { return (i + 1) % size; }

int prev(int i, int size) { return (size + i - 1) % size; }

int isFull(Buf quee) { return next(quee.tail, quee.size) == quee.head; }

int isEmpty(Buf quee) { return quee.head == quee.tail; }

Buf enque(Buf quee) {
    if (isFull(quee)) {
        printf("\nQuee is full!\n");
        return quee;
    } else {
        scanf("%d", &quee.value[quee.tail]);
        quee.tail = next(quee.tail, quee.size);
        return quee;
    }
}

Buf deque(Buf quee) {
    if (isEmpty(quee)) {
        printf("Quee is empty!");
        return quee;
    } else {
        quee.head = next(quee.head, quee.size);
        return quee;
    }
}

void echo(Buf quee) {
    int i = quee.head;
    if (isEmpty(quee))
        printf("Quee is empty!");
    else {
        while (i != quee.tail) {
            printf("%d  ", quee.value[i]);
            i = next(i, quee.size);
        }
    }
}

int main() {
    int input;
    Buf quee;
    quee.head = 0;
    quee.tail = 0;
    printf("Give size: ");
    scanf("%d", &quee.size);
    // quee.size++;
    while (1) {
        printf("\n1 -> insert\n2 -> delete\n3 -> see quee\n4 -> exit\n>>>");
        scanf("%d", &input);
        printf(">>> ");
        if (input == 1)
            quee = enque(quee);
        else if (input == 2)
            quee = deque(quee);
        else if (input == 3)
            echo(quee);
        else if (input == 4)
            break;
        else
            printf("Please chose a valid option!\n");
    }

    return 0;
}
