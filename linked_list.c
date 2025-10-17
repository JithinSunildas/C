#include <stdio.h>
#include <stdlib.h>

typedef struct Term {
    int exp;
    int coeff;
    struct Term *next;
} Term;

typedef struct {
    Term *head;
    Term *tail;
} Poly;

void init_term(Term *a) { a->next = NULL; }

void init_poly(Poly *a) {
    a->head = NULL;
    a->tail = NULL;
}

void new_term(Poly *a) {
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

void free_poly(Poly *a) {
    Term *temp = a->head;
    while (temp != NULL) {
        temp = a->head->next;
        free(a->head);
        a->head = temp;
    }
}

void read_poly(Poly *p) {
    printf("Coefficient and exponent: ");
    scanf("%d%d", &p->tail->coeff, &p->tail->exp);
}

void show_poly(Poly *p) {
    Term *rout = p->head;
    printf("\n");
    while (rout != NULL) {
        printf("%dx^%d  ", rout->coeff, rout->exp);
        rout = rout->next;
    }
}

void add_poly(Poly *a, Poly *b, Poly *c) {
    // poly a, b, c is already initialised to set heads and tails next to NULL.
    Term *i = a->head, *j = b->head, *k = c->tail;
    int coeff_sum;

    while (i != NULL && j != NULL) {
        if (i->exp == j->exp) {
            coeff_sum = i->coeff + j->coeff;
            if (coeff_sum != 0) {
                new_term(c);
                k = c->tail;
                k->exp = i->exp;
                k->coeff = coeff_sum;
            }
            i = i->next;
            j = j->next;
        } else if (i->exp < j->exp) {
            new_term(c);
            k = c->tail;
            k->exp = i->exp;
            k->coeff = i->coeff;
            i = i->next;
        } else {
            new_term(c);
            k = c->tail;
            k->exp = j->exp;
            k->coeff = j->coeff;
            j = j->next;
        }
    }

    while (i != NULL) {
        new_term(c);
        k = c->tail;
        k->exp = i->exp;
        k->coeff = i->coeff;
        i = i->next;
    }

    while (j != NULL) {
        new_term(c);
        k = c->tail;
        k->exp = j->exp;
        k->coeff = j->coeff;
        j = j->next;
    }
}

int main() {
    Poly a, b, c;
    int input;

    init_poly(&a);
    init_poly(&b);
    init_poly(&c);

    while (1) {
        printf("Give poly a\nPress 1 to enter, 2 to exit.");
        scanf("%d", &input);
        if (input == 2)
            break;
        new_term(&a);
        read_poly(&a);
    }

    while (1) {
        printf("Give poly b\nPress 1 to enter, 2 to exit.");
        scanf("%d", &input);
        if (input == 2)
            break;
        new_term(&b);
        read_poly(&b);
    }

    show_poly(&a);
    show_poly(&b);
    add_poly(&a, &b, &c);
    printf("\nOutput:");
    show_poly(&c);

    free_poly(&a);
    free_poly(&b);
    free_poly(&c);

    printf("\n");
    return 0;
}
