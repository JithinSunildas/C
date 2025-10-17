#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val;
    struct Term *next;
} Term;

typedef struct {
    Term *head;
    Term *tail;
} List;

void init_term(Term *a) { a->next = NULL; }

void init_list(List *a) {
    a->head = NULL;
    a->tail = NULL;
}

void new_term(List *a) {
    Term *temp = (Term *)malloc(sizeof(Term));
    init_term(temp);
    if (a->head == NULL) {
        a->head = temp;
        a->tail = temp;
    } else {
        a->tail->next = temp;
        a->tail = temp;
    }
}

void free_list(List *a) {
    Term *temp = a->head;
    while (temp != NULL) {
        temp = a->head->next;
        free(a->head);
        a->head = temp;
    }
}

void read_list(List *p) {
    printf("Coefficient and exponent: ");
    scanf("%d%d", &p->tail->val);
}

void show_list(List *p) {
    Term *rout = p->head;
    printf("\n");
    while (rout != NULL) {
        printf("%dx^%d  ", rout->val);
        rout = rout->next;
    }
}
int main() {
    int k;
    printf("Give number of arrays: ");
    scanf("%d", &k);

    return 0;
}
