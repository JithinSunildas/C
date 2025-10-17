#include <stdio.h>

typedef int T;
typedef struct {
    int size;
    T value[100];
    int head;
    int tail;
} Buf;

int next(int i, int size) { return (i + 1) % size; }

int prev(int i, int size) { return (size + i - 1) % size; }

int isFull(Buf deck) { return next(deck.tail, deck.size) == deck.head; }

int isEmpty(Buf deck) { return deck.head == deck.tail; }

Buf pushT(Buf deck) {
    if (isFull(deck)) {
        printf("\ndeck is full!\n");
        return deck;
    } else {
        scanf("%d", &deck.value[deck.tail]);
        deck.tail = next(deck.tail, deck.size);
        return deck;
    }
}

Buf pushF(Buf deck) {
    if (isFull(deck)) {
        printf("\ndeck is full!\n");
        return deck;
    } else {
        deck.head = prev(deck.head, deck.size);
        scanf("%d", &deck.value[deck.head]);
        return deck;
    }
}

Buf popF(Buf deck) {
    if (isEmpty(deck)) {
        printf("deck is empty!");
        return deck;
    } else {
        deck.head = next(deck.head, deck.size);
        return deck;
    }
}

Buf popT(Buf deck) {
    if (isEmpty(deck)) {
        printf("deck is empty!");
        return deck;
    } else {
        deck.tail = prev(deck.tail, deck.size);
        return deck;
    }
}
void echo(Buf deck) {
    int i = deck.head;
    if (isEmpty(deck))
        printf("deck is empty!");
    else {
        while (i != deck.tail) {
            printf("%d  ", deck.value[i]);
            i = next(i, deck.size);
        }
    }
}

int main() {
    int input;
    Buf deck;
    deck.head = 0;
    deck.tail = 0;
    printf("Give size: ");
    scanf("%d", &deck.size);
    // deck.size++;
    while (1) {
        printf("\n1 -> push front\n2 -> push back\n3 -> pop front\n4 -> pop back\n5 -> show "
               "deck\n6 -> Exit\n>>>");
        scanf("%d", &input);
        printf(">>> ");
        if (input == 1)
            deck = pushF(deck);
        else if (input == 2)
            deck = pushT(deck);
        else if (input == 3)
            deck = popF(deck);
        else if (input == 4)
            deck = popT(deck);
        else if (input == 5)
            echo(deck);
        else if (input == 6)
            break;
        else
            printf("Please chose a valid option!\n");
    }

    return 0;
}
