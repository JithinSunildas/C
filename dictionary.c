#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;
struct Node {
    char word[60];
    char meaning[500];
    struct Node *left;
    struct Node *right;
};

Node *newnode() {
    Node *node = malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert(Node **pcurrent, Node *newnode) {
    Node *current = *pcurrent;

    if (current == NULL) {
        *pcurrent = newnode;
        return;
    }

    int c = strcmp(current->word, newnode->word);

    if (c < 0)
        insert(&(current->left), newnode);
    else if (c > 0)
        insert(&(current->right), newnode);
    else
        printf("\nWord already exists in dictionary.\n");
}

void search(Node *current, char search_word[]) {
    if (current == NULL) {
        printf("Given word not found in dictionary.\n");
        return;
    }

    int c = strcmp(current->word, search_word);

    if (c < 0)
        search(current->left, search_word);
    else if (c > 0)
        search(current->right, search_word);
    else
        printf("\n%s\nmeaning: %s", current->word, current->meaning);
}

void readnode(Node *treetop) {
    Node *node = newnode();
    printf("\nword: ");
    scanf("%s", node->word);
    printf("\nmeaning: ");
    fgets(node->meaning);
    insert(&treetop, node);
    return;
}

int main() {
    char f = 'h', word[60];
    int i = 1;
    Node *treetop = NULL;

    printf("Welcome to dictionary!\n\ti\t: to insert a word.\n\ts\t: to search a word\n\tq\t: to "
           "exit\nType h for help.\n");
    while (i) {
        scanf("%c", &f);

        switch (f) {
        case 'i':
            readnode(treetop);
            break;
        case 's':
            scanf("%s", word);
            search(treetop, word);
            break;
        case 'h':
            printf("\n\ti\t: to insert a word.\n\ts\t: to search a word\n\tq\t: to exit\n");
            break;
        case 'q':
            i = 0;
            break;
        default:
            printf("\n\ti\t: to insert a word.\n\ts\t: to search a word\n\tq\t: to exit\nType h "
                   "for help.");
            break;
        }
    }

    return 0;
}
