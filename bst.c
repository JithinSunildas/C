#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node node;

struct node {
    char key[100];
    char val[100];
    node *left;
    node *right;
};

node *newNode(char k[], char v[], node *l, node *r) {
    node *ret = malloc(sizeof(node));
    strcpy(ret->key, k);
    strcpy(ret->val, v);
    ret->left = l;
    ret->right = r;
    return ret;
}

node *insert(node *x, char k[], char v[]) {
    if (x == NULL) {
        return newNode(k, v, NULL, NULL);
    }

    int c = strcmp(k, x->key);

    if (c == 0) {
    } else if (c < 0) {
        x->left = insert(x->left, k, v);
    } else {
        x->right = insert(x->right, k, v);
    }

    return x;
}

const node *search(node *x, char k[]) {
    if (x == NULL) {
        return NULL;
    }

    int c = strcmp(k, x->key);

    if (c == 0) {
        return x;
    } else if (c < 0) {
        return search(x->left, k);
    } else {
        return search(x->right, k);
    }
}

void print(node *x) {
    if (x == NULL) {
        return;
    }

    printf("[\n");
    print(x->left);
    printf("%s -> %s\n", x->key, x->val);
    print(x->right);
    printf("]\n");
}

int main() {
    int n;
    char k[100];
    char v[100];
    node *tree = NULL;

    printf("Number of items:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Please enter key-val:");
        scanf("%s", k);
        scanf("%s", v);
        tree = insert(tree, k, v);
    }

    print(tree);

    do {
        printf("Search: ");
        if (scanf("%s", k) <= 0)
            break;
        const node *x = search(tree, k);
        if (x) {
            printf("Found: %s -> %s\n", x->key, x->val);
        } else {
            printf("Not found\n");
        }
    } while (true);

    return 0;
}
