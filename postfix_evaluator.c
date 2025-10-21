#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char ch;
    struct Node *left, *right;
} Node;

Node *newNode(char ch, Node *l, Node *r) {
    Node *x = malloc(sizeof(Node));
    x->ch = ch;
    x->left = l;
    x->right = r;
    return x;
}

#define MAX_ITEMS 100
typedef struct {
    Node *data[MAX_ITEMS];
    int size;
} Stack;

void stack_init(Stack *s) { s->size = 0; }
void push(Stack *s, Node *x) {
    assert(s->size < MAX_ITEMS);
    s->data[s->size++] = x;
}
Node *pop(Stack *s) {
    assert(s->size > 0);
    return s->data[--s->size];
}
bool empty(Stack *s) { return s->size == 0; }
Node *top(Stack *s) {
    assert(s->size > 0);
    return s->data[s->size - 1];
}

bool isVal(char ch) { return ch >= '0' && ch <= '9'; }
bool isBinaryOp(char ch) { return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^'; }

Node *postfix2Tree(const char *input) {
    Stack stack;
    stack_init(&stack);
    for (int i = 0; input[i]; i++) {
        char ch = input[i];
        if (isVal(ch))
            push(&stack, newNode(ch, NULL, NULL));
        else if (isBinaryOp(ch)) {
            Node *r = pop(&stack), *l = pop(&stack);
            push(&stack, newNode(ch, l, r));
        }
    }
    Node *root = pop(&stack);
    assert(empty(&stack));
    return root;
}

void inorder(Node *x) {
    if (!x)
        return;
    printf("(");
    inorder(x->left);
    printf("%c", x->ch);
    inorder(x->right);
    printf(")");
}
void preorder(Node *x) {
    if (!x)
        return;
    printf("%c", x->ch);
    preorder(x->left);
    preorder(x->right);
}
void postorder(Node *x) {
    if (!x)
        return;
    postorder(x->left);
    postorder(x->right);
    printf("%c", x->ch);
}

int eval(Node *x) {
    if (isVal(x->ch))
        return x->ch - '0';
    int a = eval(x->left), b = eval(x->right);
    switch (x->ch) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return pow(a, b);
    }
    return 0;
}

int main() {
    char input[100];
    printf("Enter postfix expression: ");
    scanf("%s", input);

    Node *root = postfix2Tree(input);

    printf("Infix form: ");
    inorder(root);
    printf("\n");
    printf("Prefix form: ");
    preorder(root);
    printf("\n");
    printf("Postfix form: ");
    postorder(root);
    printf("\n");

    printf("Result: %d\n", eval(root));
}

// Output
// Enter postfix expression: 34+42^-
// Infix form: (((3)+(4))-((4)^(2)))
// Prefix form: -+34^42
// Postfix form: 34+42^-
// Result: -9
