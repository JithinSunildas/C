#include <stdio.h>

typedef struct {
    int coeff;
    int exp;
} Poly;

void read_poly(Poly *p, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("Coefficient: ");
        scanf("%d", &p->coeff);
        printf("Exponent: ");
        scanf("%d", &p->exp);
        p++;
    }
}

void echo_poly(Poly *p, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%dx^%d  ", p->coeff, p->exp);
        p++;
    }
    printf("\n");
}

void sort_poly(Poly *p, int size) {
    int i, j;
    Poly temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i; j++) {
            if (p->exp > (p + 1)->exp) {
                temp = *p;
                *p = *(p + 1);
                *(p + 1) = temp;
                p++;
            }
        }
    }
}

// since we have 2 integers as members in the Poly struct, we can use them to pass sizes of 2
// polybomials.
void add_poly(Poly *a, Poly *b, Poly *c, Poly *size) {
    int i, j, m, n;
    m = size->coeff;
    n = size->exp;
    if (m > n) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                if (a->exp == b->exp) {
                    c->coeff = a->coeff + b->coeff;
                    a++;
                    b++;
                    c++;
                } else if (a->exp > b->exp) {
                    c->coeff = b->coeff;
                    b++;
                    c++;
                } else {
                    c->coeff = a->coeff;
                    a++;
                    c++;
                }
            }
        }
    } else {
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                if (a->exp == b->exp) {
                    c->coeff = a->coeff + b->coeff;
                    a++;
                    b++;
                    c++;
                } else if (a->exp > b->exp) {
                    c->coeff = b->coeff;
                    b++;
                    c++;
                } else {
                    c->coeff = a->coeff;
                    a++;
                    c++;
                }
            }
        }
    }
}

int main() {
    int m, n;

    printf("Give length of first polynomial: ");
    scanf("%d", &m);
    Poly a[m];
    // passing the memory address of the first index.
    read_poly(&a[0], m);
    printf("\n");

    printf("Give length of second polynomial: ");
    scanf("%d", &n);
    Poly b[n];
    read_poly(&b[0], n);
    printf("\n");

    // the polynomial array should be sorted for the algorithm to work.
    sort_poly(&a[0], m);
    sort_poly(&b[0], n);

    Poly c[m + n], size;
    // usinf a structure to pass both of the sizes to the adding function.
    size.coeff = m;
    size.exp = n;
    add_poly(&a[0], &b[0], &c[0], &size);

    echo_poly(&c[0], m + n);
    printf("\n");

    return 0;
}
