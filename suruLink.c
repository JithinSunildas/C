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

void poly_init(poly *p) { p->head = NULL; }

void term_insert(poly *p, term *pc, term *x) {
    if (p->head == NULL && pc == NULL) {
        p->head = x;
    } else {
        x->next = pc->next;
        pc->next = x;
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

void term_print(term *t) { printf("%dx^%d ", t->coef, t->exp); }

void term_read(term *t) {
    printf("enter the coef and expo in sorted order \n");
    scanf("%d%d", &t->coef, &t->exp);
}

void poly_print(poly *p) {
    if (p->head == NULL) {
        printf("empty");
    } else
        for (term *t = p->head; t != NULL; t = t->next) {
            term_print(t);
        }
}

void poly_read(poly *p) {
    int size;
    int i;
    p->head = NULL;
    term *pa = NULL;
    printf("enter the number of terms\n");
    scanf("%d", &size);
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
    poly_init(&a);
    poly_init(&b);
    poly_init(&c);
    poly_read(&a);
    poly_print(&a);
    printf("\n");
    poly_read(&b);
    poly_print(&b);
    printf("\n");
    add_poly(&a, &b, &c);
    poly_print(&c);
    printf("\n");
    return 0;
}
