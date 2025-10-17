#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//
// Assignment:
//   Implement heapsort
//
// For the questions, read the code/comments below.

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

// Binary heap
static inline int left(int i) { return 2 * i + 1; }
static inline int right(int i) { return 2 * i + 2; }
static inline int parent(int i) { return (i - 1) / 2; }

void shiftDown(int data[], int size, int x);
void heapify(int data[], int size);
void heapsort(int data[], int size);

// heapsort.c

// S3_PCCST303_ASSIGNMENT_BEGIN

// shiftDown
//
// Input:
// Given a Maxheap where every node satisfies the heap property
// ie: Every node value is >= than that of it's immediate children
// but the value at x is lower than at least one of the children
// thus causing node x to fail to satisfy heap property
//
// Output: Maxheap, ie: ensure all nodes satisfy the heap property
//
// Idea:
//  Shift/Swap the node x with the children with max value, say y
//  Now the node x will satisfy the heap property but that child node y may not
//  Repeat the same at that child y if its heap property is not satisfied
//

// Any helper function needed to write shiftDown goes here
//
// Heapify
// Two ways to construct a binary heap from a given array
//   Start with array of 1 element. It is a binary heap
//   Now take the second element, and insert into that binary heap
//   Repeat.
//
//   Time complexity:= Sum of depths = Sum O(i)
//                   = O(log 2 + log 3 + log 4 + .. + log n)
//                   = O (n*log n)
//
//   Can we do better? In O(N)?
//
//   We start from the last level, and make it a heap by using shiftDown
//      Time complexity : n/2 * 1*k
//   We go to l-1 th level:
//      Notice their children are already heap,
//      So every node except only value l-1th node may be lower than its
//      children, We could fix them by using shiftDown
//   we make each tree at l-1 th level, a heap, by using shiftDown
//      Time complexity : n/4 * 2*k
//   Repeat
//
//   Time complexity:=
//                   = n/2 * 1 + n/4 * 2 + n/8 * 3 + n/16 * 4 + ...
//                   = n * ( 1/2 + 2/4 + 3/8 + 4/16 + ... )
//                   <= n * 2
//                   = O(n)
//

// Assignment...
//
void shiftDown(int data[], int size, int x) {
    if (x > size)
        return;
    else if (data[x] < data[left(x)]) {
        swap(&data[x], &data[left(x)]);
        shiftDown(data, size, data[left(x)]);
    } else if (data[x] < data[right(x)]) {
        swap(&data[x], &data[right(x)]);
        shiftDown(data, size, data[right(x)]);
    }
}

// Heapify
void heapify(int data[], int size) {}

// Implement Heap sort
void heapsort(int data[], int size) {}

// S3_PCCST303_ASSIGNMENT_END

// test.c

// Asserts
void assertMaxheap(int data[], int size) {
    for (int i = 0; i < size; i++) {
        if (left(i) < size) {
            assert(geq(data[i], data[left(i)]));
        }
        if (right(i) < size) {
            assert(geq(data[i], data[right(i)]));
        }
    }
}

void assertSorted(int data[], int size) {
    for (int i = 1; i < size; i++) {
        assert(leq(data[i - 1], data[i]));
    }
}

void prop_heapify(int data[], int size) {
    print("input", data, size);
    heapify(data, size);
    print("heapified", data, size);
    assertMaxheap(data, size);
}

void prop_heapsort(int data[], int size) {
    print("input", data, size);
    heapsort(data, size);
    print("heapsorted", data, size);
    assertSorted(data, size);
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
        printf("Test4(%d)\n", t);
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
        printf("Test8(%d)\n", t);
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
    printf("\n!! Congratulations, all tests passed !!\n");
    return 0;
}
