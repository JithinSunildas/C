#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char url[100];
    struct Node *prev;
    struct Node *next;
} Node;

Node *head = NULL;
Node *curr = NULL;

void visit(char *url) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->url, url);
    newNode->prev = curr;
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
        curr = newNode;
    } else {
        Node *tmp = curr->next;
        while (tmp != NULL) {
            Node *del = tmp;
            tmp = tmp->next;
            free(del);
        }
        curr->next = newNode;
        newNode->prev = curr;
        curr = newNode;
    }
    printf("Visited:%s\n", curr->url);
}

void backward() {
    if (curr != NULL && curr->prev != NULL) {
        curr = curr->prev;
        printf("Moved backward.Current page:%s\n", curr->url);
    } else {
        printf("No previous page\n");
    }
}

void forward() {
    if (curr != NULL && curr->next != NULL) {
        curr = curr->next;
        printf("Moved forward.Current page:%s\n", curr->url);
    } else {
        printf("No forward page\n");
    }
}

void showCurrent() {
    if (curr != NULL) {
        printf("current page:%s\n", curr->url);
    } else {
        printf("No page visited yet\n");
    }
}

int main() {
    int choice;
    char url[100];
    while (1) {
        printf("Browser navigation\n 1.Visit a new page\n 2.Backward\n 3.Forward\n 4.Show current "
               "page\n 5.Exit\n");
        printf("Enter your choice:");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Enter the page url:");
            scanf("%s", url);
            visit(url);
            break;
        case 2:
            backward();
            break;
        case 3:
            forward();
            break;
        case 4:
            showCurrent();
            break;
        case 5:
            printf("Exiting the program\n");
            exit(0);
        default:
            printf("invalid choice");
        }
        printf("\n");
    }
    return 0;
}
