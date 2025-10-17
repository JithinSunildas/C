#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct term {
    int coef;
    int exp;
    struct term *next;
} term;
typedef struct poly {
    term *head;
} poly;

term *term_alloc() {
    term *p = malloc(sizeof(term));
    return p;
}

void term_init(term *t, int coef, int exp) {
    t->coef = coef;
    t->exp = exp;
    t->next = NULL;
}
bool empty(poly *p) { return p->head == NULL; }
void term_insert(poly *p, term *t, term *x) {
    if (empty(p) || t == NULL) {
        x->next = p->head;
        p->head = x;
    } else {
        x->next = t->next;
        t->next = x;
    }
}
void term_free(term *p) {
    if (p->next != NULL) {
        term_free(p->next);
        p->next = NULL;
    }
    free(p);
}
void poly_init(poly *p) { p->head = NULL; }
void poly_free(poly *p) {
    if (p->head != NULL) {
        term_free(p->head);
        p->head = NULL;
    }
}
void add_poly(poly *a, poly *b, poly *c) {
    term *pa;
    term *pb;
    term *pc;
    pa = a->head;
    pb = b->head;
    pc = NULL;
    while (pa != 0 && pb != 0) {
        if (pa->exp == pb->exp) {
            if ((pa->coef + pb->coef) != 0) {
                term *x = term_alloc();
                term_init(x, pa->coef + pb->coef, pa->exp);
                term_insert(c, pc, x);
                pc = x;
            }
            pa = pa->next;
            pb = pb->next;
        } else if (pa->exp < pb->exp) {
            term *x = term_alloc();
            term_init(x, pa->coef, pa->exp);
            term_insert(c, pc, x);
            pc = x;
            pa = pa->next;
        } else {
            term *x = term_alloc();
            term_init(x, pb->coef, pb->exp);
            term_insert(c, pc, x);
            pc = x;
            pb = pb->next;
        }
    }
    while (pa != 0) {
        term *x = term_alloc();
        term_init(x, pa->coef, pa->exp);
        term_insert(c, pc, x);
        pc = x;
        pa = pa->next;
    }
    while (pb != 0) {
        term *x = term_alloc();
        term_init(x, pb->coef, pb->exp);
        term_insert(c, pc, x);
        pc = x;
        pb = pb->next;
    }
}

void term_print(term *t) {
    if (t == NULL) {
        printf("null term");
    }
    printf("%dx^%d ", t->coef, t->exp);
    return;
}
void term_read(term *t) {
    printf("enter the coef and expo in sorted order ");
    scanf("%d%d", &t->coef, &t->exp);
}
void poly_print(poly *p) {
    if (p->head == NULL) {
        printf("List null");
    } else {
        term_print(p->head);
        for (term *t = p->head->next; t != NULL; t = t->next) {
            term_print(t);
        }
    }
    printf("\n");
}
void poly_read(poly *p) {
    int size;
    int i;
    printf("enter the number of terms");
    scanf("%d", &size);
    p->head = NULL;
    term *pa = NULL;
    for (i = 0; i < size; i++) {
        term *x = term_alloc();
        term_init(x, 0, 0);
        term_read(x);
        term_insert(p, pa, x);
        pa = x;
    }
}

int main() {
    poly a;
    poly b;
    poly c;
    poly_read(&a);
    printf("First poly :");
    poly_print(&a);
    poly_read(&b);
    printf("Second poly :");
    poly_print(&b);
    add_poly(&a, &b, &c);
    printf("Output :");
    poly_print(&c);
    return 0;
}
