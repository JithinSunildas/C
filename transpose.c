#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//
// Assignment:
//   Find the transpose of a sparse matrix represented in array.
//
// For the questions, read the code/comments below.

// matrix.h
struct term {
    int row;
    int col;
    int val;
};
typedef struct term term;

void print(const char *name, term data[], int size);

//
// Input: data,size : SparseMatrix with size terms.
//                    terms are sorted in increasing order by (row,col),
//                    terms with zero values are excluded,
//                    there is at most one term for each (row,col)
//                    row,col are >= zero
// Output: out      : SparseMatrix with size terms.
//                    terms are sorted in increasing order by (row,col),
//                    terms with zero values are excluded,
//                    there is at most one term for each (row,col)
//
int transpose(term data[], int size, term out[]);

// matrix.c

void print(const char *name, term data[], int size) {
    printf("%s: [", name);
    for (int i = 0; i < size; i++) {
        printf("(%d,%d,%d),", data[i].row, data[i].col, data[i].val);
    }
    printf("]\n");
}

// transpose.c

//
// Input: data,size : SparseMatrix with size terms.
//                    terms are sorted in increasing order by (row,col),
//                    terms with zero values are excluded,
//                    there is at most one term for each (row,col)
//                    row,col are >= zero
// Output: out      : SparseMatrix with size terms.
//                    terms are sorted in increasing order by (row,col),
//                    terms with zero values are excluded,
//                    there is at most one term for each (row,col)
//

// S3_PCCST303_ASSIGNMENT_BEGIN

// Please feel free to modify the code below

//
// Assignment:
//   Find the transpose of a sparse matrix represented in array.
//
//
//  for(int i=0; i<size; i++){
//    out[i].row = data[i].col;
//    out[i].col = data[i].row;
//    out[i].val = data[i].val;
//  }
//
// Q1. What is the problem with just swapping the row and col?
//      Choices:
//        A) The out will be sorted by (row,col)
//        B) The out may not be sorted by (row,col) but it will be sorted by row
//        C) The out may not be sorted by (row,col) but it will be sorted by col
//        D) The out may not be sorted by (row,col), row nor col
//
//
//
// Q2. Making use of the above, how do you design an algorithm to transpose?
//     Which sorting algorithm will you choose? Justify. State your assumptions,
//     if any.
//
//
//
// Q3. Implement the above algorithm to transpose below
//

int transpose(term data[], int size, term out[]) {
    int k = 0, max_col = 0;
    for (int i = 0; i < size; i++) {
        if (data[i].col > max_col)
            max_col = data[i].col;
    }
    for (int i = 0; i <= max_col; i++) {
        for (int j = 0; j < size; j++) {
            if (data[j].col == i) {
                out[k].row = data[j].col;
                out[k].col = data[j].row;
                out[k].val = data[j].val;
                k++;
            }
        }
    }
    return 0;
}

// S3_PCCST303_ASSIGNMENT_END

// test.c

int countRCV(term data[], int size, int r, int c, int v) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (data[i].row == r && data[i].col == c && data[i].val == v) {
            count++;
        }
    }
    return count;
}

void assertSamecount(term data[], int size, term out[]) {

    for (int i = 0; i < size; i++) {
        int r = data[i].row;
        int c = data[i].col;
        int v = data[i].val;

        // count (rcv) in data and (crv) in out should be same
        assert(countRCV(data, size, r, c, v) == countRCV(out, size, c, r, v));
    }
}

int leq(term x, term y) { return (x.row < y.row) || ((x.row == y.row) && (x.col <= y.col)); }

void assertSorted(term data[], int size) {
    for (int i = 1; i < size; i++) {
        assert(leq(data[i - 1], data[i]));
    }
}

int prop_transpose(term data[], int size) {
    term *out = malloc(size * sizeof(term));
    print("input", data, size);
    assertSorted(data, size);
    transpose(data, size, out);
    print("output", out, size);
    assertSamecount(data, size, out);
    assertSorted(out, size);
}

void test1() {
    printf("Test1\n");

    term xxx[] = {
        {1, 2, 10}, {1, 3, 20}, {2, 1, 30}, {2, 3, 40}, {3, 3, 50}, {3, 4, 60},
    };

    prop_transpose(xxx, sizeof(xxx) / sizeof(xxx[0]));
}

void test2() {
    printf("Test2\n");

    term xxx[] = {{0, 2, 10}, {0, 3, 20}, {1, 1, 30}, {2, 3, 40},
                  {3, 3, 50}, {3, 4, 60}, {5, 5, 70}};

    prop_transpose(xxx, sizeof(xxx) / sizeof(xxx[0]));
}

void test3() {
    for (int t = 0; t < 5; t++) {
        printf("Test3(%d)\n", t);
        int size = 1 + rand() % 10;
        term *data = malloc(size * sizeof(term));
        int x = 0;
        for (int i = 0; i < size; i++) {
            x += rand() % 10;
            data[i].row = x / 10;
            data[i].col = x % 10;
            data[i].val = x;
        }

        prop_transpose(data, size);
        free(data);
    }
}

int main() {
    srand(time(0));
    test1();
    test2();
    test3();
    printf("\n!! Congratulations, all tests passed !!\n");
    return 0;
}
