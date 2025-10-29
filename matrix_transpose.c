#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

enum { MAXTERMS = 100 };
enum { MAXROWSCOLS = 100 };

struct term {
    int row;
    int col;
    int val;
};
typedef struct term term;

struct matrix {
    int size;
    term terms[MAXTERMS];
};
typedef struct matrix matrix;

void matrix_transpose_unsorted(const matrix *a, matrix *b) {
    for (int i = 0; i < a->size; i++) {
        b->terms[i].row = a->terms[i].col;
        b->terms[i].col = a->terms[i].row;
        b->terms[i].val = a->terms[i].val;
    }
    b->size = a->size;
}

void matrix_countingsort_by_rowcol(const matrix *a, matrix *b) {
    int count[MAXROWSCOLS];
    int prefixsum[MAXROWSCOLS];

    // init to 0
    for (int i = 0; i < MAXROWSCOLS; i++) {
        count[i] = 0;
    }

    // count the number of terms in each row
    for (int i = 0; i < a->size; i++) {
        int key = a->terms[i].row;
        count[key]++;
    }

    // // print
    // for(int i=0; i<MAXROWSCOLS; i++){
    //   printf(" %d ", count[i]);
    // }
    // printf("\n");

    // calculate the prefix sum of count[]
    prefixsum[0] = 0;
    for (int i = 1; i < MAXROWSCOLS; i++) {
        prefixsum[i] = prefixsum[i - 1] + count[i - 1];
    }

    // // print
    // for(int i=0; i<MAXROWSCOLS; i++){
    //   printf(" %d ", prefixsum[i]);
    // }
    // printf("\n");

    // copy at right location
    for (int i = 0; i < a->size; i++) {
        int key = a->terms[i].row;
        b->terms[prefixsum[key]] = a->terms[i];
        prefixsum[key]++;
    }
    b->size = a->size;
}

void term_print(term t) { printf("(%d,%d)=%d", t.row, t.col, t.val); }
void term_read(term *t) {
    printf("row col and val? ");
    scanf("%d %d %d", &t->row, &t->col, &t->val);
}

void matrix_print(const char *name, const matrix *a) {
    int i = 0;
    printf("matrix %s with %d terms: ", name, a->size);
    if (a->size == 0) {
        printf("empty");
    } else {
        term_print(a->terms[0]);
    }
    for (i = 1; i < a->size; i++) {
        printf(" , ");
        term_print(a->terms[i]);
    }
    printf("\n");
}

void matrix_read(const char *name, matrix *a) {
    int i = 0;
    printf("Number of terms in matrix %s? ", name);
    scanf("%d", &a->size);
    for (i = 0; i < a->size; i++) {
        term_read(&a->terms[i]);
    }
}

int main() {
    matrix a, b, c;
    matrix_read("a", &a);
    matrix_print("a", &a);
    matrix_transpose_unsorted(&a, &b);
    matrix_print("transposed_unsorted", &b);
    matrix_countingsort_by_rowcol(&b, &c);
    matrix_print("transposed_sorted", &c);
    return 0;
}
