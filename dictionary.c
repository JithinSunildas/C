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
    if (c > 0) // Fixed: swap left/right logic
        insert(&(current->left), newnode);
    else if (c < 0)
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
    if (c > 0)
        search(current->left, search_word);
    else if (c < 0)
        search(current->right, search_word);
    else
        printf("\n%s\nmeaning: %s\n", current->word, current->meaning);
}

void readnode(Node **treetop) {
    Node *node = newnode();
    printf("\nword: ");
    scanf("%s", node->word);
    printf("meaning: ");
    getchar();
    fgets(node->meaning, sizeof(node->meaning), stdin);

    size_t len = strlen(node->meaning);
    if (len > 0 && node->meaning[len - 1] == '\n')
        node->meaning[len - 1] = '\0';

    insert(treetop, node);
}

int main() {
    char f;
    char word[60];
    int i = 1;
    Node *treetop = NULL;

    printf("Welcome to dictionary!\n");
    printf("\ti\t: to insert a word.\n");
    printf("\ts\t: to search a word\n");
    printf("\tq\t: to exit\n");
    printf("Type h for help.\n\n");

    while (i) {
        printf("> ");
        scanf(" %c", &f);

        switch (f) {
        case 'i':
            readnode(&treetop);
            break;
        case 's':
            printf("Enter word to search: ");
            scanf("%s", word);
            search(treetop, word);
            break;
        case 'h':
            printf("\n\ti\t: to insert a word.\n");
            printf("\ts\t: to search a word\n");
            printf("\tq\t: to exit\n\n");
            break;
        case 'q':
            printf("Goodbye!\n");
            i = 0;
            break;
        default:
            printf("\nInvalid option. Type h for help.\n\n");
            break;
        }
    }
    return 0;
}
