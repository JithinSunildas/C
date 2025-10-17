#include <stdio.h>

struct term {
    int coeff;
    int expo;
};

struct poly {
    int n;
    struct term t[100];
} a, b, c;

void reada() {
    printf("Enter the size of the first polynomial: ");
    scanf("%d", &a.n);
    printf("Enter the coeff and expo (e.g., 5 2 for 5x^2): ");
    for (int i = 0; i < a.n; i++) {
        scanf("%d%d", &a.t[i].coeff, &a.t[i].expo);
    }
}

void readb() {
    printf("Enter the size of the second polynomial: ");
    scanf("%d", &b.n);
    printf("Enter the coeff and expo (e.g., 3 1 for 3x): ");
    for (int i = 0; i < b.n; i++) {
        scanf("%d%d", &b.t[i].coeff, &b.t[i].expo);
    }
}

void addfunction() {
    int ia, ib, ic;
    ia = ib = ic = 0;

    while (ia < a.n && ib < b.n) {
        if (a.t[ia].expo == b.t[ib].expo) {
            if (a.t[ia].coeff + b.t[ib].coeff != 0) {
                c.t[ic].expo = a.t[ia].expo;
                c.t[ic].coeff = a.t[ia].coeff + b.t[ib].coeff;
                ic++;
            }
            ia++;
            ib++;
        } else if (a.t[ia].expo > b.t[ib].expo) {
            c.t[ic].coeff = a.t[ia].coeff;
            c.t[ic].expo = a.t[ia].expo;
            ia++;
            ic++;
        } else {
            c.t[ic].coeff = b.t[ib].coeff;
            c.t[ic].expo = b.t[ib].expo;
            ib++;
            ic++;
        }
    }

    while (ia < a.n) {
        c.t[ic].coeff = a.t[ia].coeff;
        c.t[ic].expo = a.t[ia].expo;
        ia++;
        ic++;
    }

    while (ib < b.n) {
        c.t[ic].coeff = b.t[ib].coeff;
        c.t[ic].expo = b.t[ib].expo;
        ib++;
        ic++;
    }
    c.n = ic;
}

void displayfunction() {
    int i;
    printf("First polynomial is: ");
    for (i = 0; i < a.n; i++) {
        printf("%dx^%d", a.t[i].coeff, a.t[i].expo);
        if (i != a.n - 1)
            printf(" + ");
    }
    printf("\n");

    printf("Second polynomial is: ");
    for (i = 0; i < b.n; i++) {
        printf("%dx^%d", b.t[i].coeff, b.t[i].expo);
        if (i != b.n - 1)
            printf(" + ");
    }
    printf("\n");

    printf("Result is: ");
    if (c.n == 0) {
        printf("0\n");
        return;
    }
    for (i = 0; i < c.n; i++) {
        printf("%dx^%d", c.t[i].coeff, c.t[i].expo);
        if (i != c.n - 1)
            printf(" + ");
    }
    printf("\n");
}

int main() {
    reada();
    readb();
    addfunction();
    displayfunction();
    return 0;
}
