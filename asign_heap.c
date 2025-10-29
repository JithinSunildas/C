#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//
// assignment:
//   implement heapsort
//
// for the questions, read the code/comments below.

// heap.h

static inline bool geq(int a, int b) { return a >= b; }
static inline bool leq(int a, int b) { return a <= b; }
static inline void swap(int *p, int *q) {
    int tmp = *p;
    *p = *q;
    *q = tmp;
}

static inline void print(const char *name, int data[], int size) {
    printf("%s :\n", name);
    for (int i = 0; i < size; i++) {
        if (((i + 1) & (i)) == 0)
            printf("|");
        printf(" %d ", data[i]);
    }
    printf("\n");
}

// binary heap
static inline int left(int i) { return 2 * i + 1; }
static inline int right(int i) { return 2 * i + 2; }
static inline int parent(int i) { return (i - 1) / 2; }

void shiftdown(int data[], int size, int x);
void heapify(int data[], int size);
void heapsort(int data[], int size);

// heapsort.c

// s3_pccst303_assignment_begin

// shiftdown
//
// input:
// given a maxheap where every node satisfies the heap property
// ie: every node value is >= than that of it's immediate children
// but the value at x is lower than at least one of the children
// thus causing node x to fail to satisfy heap property
//
// output: maxheap, ie: ensure all nodes satisfy the heap property
//
// idea:
//  shift/swap the node x with the children with max value, say y
//  now the node x will satisfy the heap property but that child node y may not
//  repeat the same at that child y if its heap property is not satisfied
//

// any helper function needed to write shiftdown goes here

void shiftdown(int data[], int size, int x) {
    int l = left(x), r = right(x), largest = x;

    if (l < size && data[l] > data[largest])
        largest = l;

    if (r < size && data[r] > data[largest])
        largest = r;

    if (largest != x) {
        swap(&data[largest], &data[x]);
        shiftdown(data, size, largest);
    }
}

// heapify
//
// two ways to construct a binary heap from a given array
//   start with array of 1 element. it is a binary heap
//   now take the second element, and insert into that binary heap
//   repeat.
//
//   time complexity:= sum of depths = sum o(i)
//                   = o(log 2 + log 3 + log 4 + .. + log n)
//                   = o (n*log n)
//
//   can we do better? in o(n)?
//
//   we start from the last level, and make it a heap by using shiftdown
//      time complexity : n/2 * 1*k
//   we go to l-1 th level:
//      notice their children are already heap,
//      so every node except only value l-1th node may be lower than its
//      children, we could fix them by using shiftdown
//   we make each tree at l-1 th level, a heap, by using shiftdown
//      time complexity : n/4 * 2*k
//   repeat
//
//   time complexity:=
//                   = n/2 * 1 + n/4 * 2 + n/8 * 3 + n/16 * 4 + ...
//                   = n * ( 1/2 + 2/4 + 3/8 + 4/16 + ... )
//                   <= n * 2
//                   = o(n)
//
void heapify(int data[], int size) {
    for (int x = size - 1; x > 0; x--) {
        shiftdown(data, size, parent(x));
    }
}

// implement heap sort
void heapsort(int data[], int size) {
    // qc: your code goes here
    // expected lines of code: 3-4.
    // please do not write more than 10 lines of code
    heapify(data, size);
    for (int i = size - 1; i > 0; i--) {
        swap(&data[0], &data[i]);
        shiftdown(data, i, 0);
    }
}

// s3_pccst303_assignment_end

// test.c

// asserts
void assertmaxheap(int data[], int size) {
    for (int i = 0; i < size; i++) {
        if (left(i) < size) {
            assert(geq(data[i], data[left(i)]));
        }
        if (right(i) < size) {
            assert(geq(data[i], data[right(i)]));
        }
    }
}

void assertsorted(int data[], int size) {
    for (int i = 1; i < size; i++) {
        assert(leq(data[i - 1], data[i]));
    }
}

void prop_heapify(int data[], int size) {
    print("input", data, size);
    heapify(data, size);
    print("heapified", data, size);
    assertmaxheap(data, size);
}

void prop_heapsort(int data[], int size) {
    print("input", data, size);
    heapsort(data, size);
    print("heapsorted", data, size);
    assertsorted(data, size);
}

void test1() {
    int data[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int size = sizeof(data) / sizeof(data[0]);
    prop_heapify(data, size);
}

void test2() {
    int data[] = {1, 4, 1, 4, 2, 1, 3, 5, 6, 2, 3};
    int size = sizeof(data) / sizeof(data[0]);
    prop_heapify(data, size);
}

void test3() {
    int data[] = {2, 7, 1, 8, 2, 8, 1, 8, 2, 8, 4, 5, 9, 0, 4, 5};
    int size = sizeof(data) / sizeof(data[0]);
    prop_heapify(data, size);
}

void test4() {
    for (int t = 0; t < 5; t++) {
        printf("test4(%d)\n", t);
        int size = 1 + rand() % 10;

        int *data = malloc(size * sizeof(int));

        for (int i = 0; i < size; i++) {
            data[i] = rand() % 10;
        }

        prop_heapify(data, size);

        free(data);
    }
}

void test5() {
    int data[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int size = sizeof(data) / sizeof(data[0]);
    prop_heapsort(data, size);
}

void test6() {
    int data[] = {1, 4, 1, 4, 2, 1, 3, 5, 6, 2, 3};
    int size = sizeof(data) / sizeof(data[0]);
    prop_heapsort(data, size);
}

void test7() {
    int data[] = {2, 7, 1, 8, 2, 8, 1, 8, 2, 8, 4, 5, 9, 0, 4, 5};
    int size = sizeof(data) / sizeof(data[0]);
    prop_heapsort(data, size);
}

void test8() {
    for (int t = 0; t < 5; t++) {
        printf("test8(%d)\n", t);
        int size = 1 + rand() % 10;

        int *data = malloc(size * sizeof(int));

        for (int i = 0; i < size; i++) {
            data[i] = rand() % 10;
        }

        prop_heapsort(data, size);

        free(data);
    }
}

int main() {
    srand(time(0));
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    printf("\n!! congratulations, all tests passed !!\n");
    return 0;
}
