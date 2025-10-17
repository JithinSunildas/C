#include <stdio.h>
typedef struct {
    int front;
    int back;
    int *data;
    int size;
} lin;

void enque(lin *a, int x) {
    int i, n;
    if (a->front == 0 && a->back == a->size - 1) {
        printf("Queue is full\n");
        return;
    } else if (a->back == a->size - 1) {
        n = a->back - a->front;
        for (i = 0; i < n; i++) {
            a->data[i] = a->data[a->front + i];
        }
        a->front = 0;
        a->back = n;
        a->data[a->back++] = x;
    } else {
        a->data[a->back++] = x;
    }
}
void deque(lin *a) {
    if (a->front == a->back) {
        printf("Que is empty\n");
        return;
    }
    a->front++;
}
void display(lin *a) {
    if (a->front == a->back) {
        printf("Que is empty\n");
        return;
    }

    printf("Que content is :");
    int i = a->front;
    while (i != a->back) {
        printf("%d  ", a->data[i]);
        i++;
    }
    printf("\n");
}
int main() {
    int x;
    lin a;
    int choice;
    a.front = 0;
    a.back = 0;
    printf("Enter the size :");
    scanf("%d", &a.size);
    int arr[a.size];
    a.data = arr;
    while (1) {
        printf("Enter 1 for enque\n");
        printf("Enter 2 for dequeue\n");
        printf("Enter 3 for display\n");
        printf("Enter 4 for exit\n");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter the number to enque :");
            scanf("%d", &x);
            enque(&a, x);
            break;
        case 2:
            deque(&a);
            break;
        case 3:
            display(&a);
            break;
        case 4:
            return 0;
        default:
            printf("Invalid choice");
        }
    }
    return 0;
}
