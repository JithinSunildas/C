#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>

//
// Assignment:
//   Implement First-fit, Best-fit and Worst-fit
//   allocation algorithms using array
//
// For the questions, read the code/comments below.

// alloc.h

typedef struct Node Node;
struct Node {
    int size;
};

static inline int cmp(Node a, Node b) { return a.size - b.size; }
int first_fit(Node blocks[], int n, int request_size);
int best_fit(Node blocks[], int n, int request_size);
int worst_fit(Node blocks[], int n, int request_size);

// alloc.c

// S3_PCCST303_ASSIGNMENT_BEGIN

// Please feel free to modify the code below
int first_fit(Node blocks[], int n, int request_size) {
    for (int i = 0; i < n; i++) {
        if (request_size <= blocks[i].size) {
            blocks[i].size -= request_size;
            return i;
            break;
        }
    }
    return -1;
}

int best_fit(Node blocks[], int n, int request_size) {
    int min = -1, curr_min = -1;
    for (int i = 0; i < n; i++) {
        if (blocks[i].size >= request_size) {
            min = i;
            curr_min = blocks[i].size;
            break;
        }
    }
    if (min == -1) {
        return -1;
    }
    for (int i = min + 1; i < n; i++) {
        if (blocks[i].size >= request_size && blocks[i].size < curr_min) {
            min = i;
            curr_min = blocks[i].size;
        }
    }
    blocks[min].size -= request_size;
    return min;
}

int worst_fit(Node blocks[], int n, int request_size) {
    int max = -1, curr_max = -1;
    for (int i = 0; i < n; i++) {
        if (blocks[i].size >= request_size) {
            max = i;
            curr_max = blocks[i].size;
            break;
        }
    }
    if (max == -1) {
        return -1;
    }
    for (int i = max + 1; i < n; i++) {
        if (blocks[i].size >= request_size && blocks[i].size > curr_max) {
            max = i;
            curr_max = blocks[i].size;
        }
    }
    blocks[max].size -= request_size;
    return max;
}

// S3_PCCST303_ASSIGNMENT_END

// test.c

void assertAllInRange(const Node data[], int size, Node begin, Node end) {
    for (int i = 0; i < size; i++) {
        assert(cmp(begin, data[i]) <= 0 && cmp(data[i], end) < 0);
    }
}
void assertNoneInRange(const Node data[], int size, Node begin, Node end) {
    for (int i = 0; i < size; i++) {
        assert(!(cmp(begin, data[i]) <= 0 && cmp(data[i], end) < 0));
    }
}
void assertAllLTE(const Node data[], int size, Node x) {
    for (int i = 0; i < size; i++) {
        assert(cmp(data[i], x) <= 0);
    }
}
void assertAllEqual(const Node a[], const Node b[], int size) {
    for (int i = 0; i < size; i++) {
        assert(cmp(a[i], b[i]) == 0);
    }
}
void assertAllEqualBut(const Node a[], const Node b[], int size, int k) {
    for (int i = 0; i < size; i++) {
        if (i != k) {
            assert(cmp(a[i], b[i]) == 0);
        }
    }
}

void copyFromTo(Node a[], Node b[], int size) {
    for (int i = 0; i < size; i++) {
        b[i] = a[i];
    }
}

void print(const char *name, Node a[], int size) {
    printf("%s: ", name);
    for (int i = 0; i < size; i++) {
        printf(" %d ", a[i].size);
    }
    printf("\n");
}
Node toNode(int x) {
    Node ret;
    ret.size = x;
    return ret;
}

void prop_firstfit(Node blocks[], int nb, const int req_array[], int nr) {
    Node blocks_copy[nb];
    printf("\nTesting firstfit\n");
    for (int i = 0; i < nr; i++) {
        copyFromTo(blocks, blocks_copy, nb);

        print("Before firstfit", blocks, nb);
        int x = first_fit(blocks, nb, req_array[i]);
        printf("%d bytes allocated from block %d by firstfit\n", req_array[i], x);
        print("After firstfit", blocks, nb);

        if (x == -1) {
            assertAllInRange(blocks_copy, nb, toNode(0), toNode(req_array[i]));
            assertAllEqual(blocks, blocks_copy, nb);
        } else {
            assert(x >= 0 && x < nb);
            assert(blocks_copy[x].size >= req_array[i]);
            assertAllInRange(blocks_copy, x, toNode(0), toNode(req_array[i]));
            assertAllEqualBut(blocks, blocks_copy, nb, x);
            assert(blocks[x].size >= 0 && blocks[x].size + req_array[i] == blocks_copy[x].size);
        }
    }
}
void prop_bestfit(Node blocks[], int nb, const int req_array[], int nr) {
    Node blocks_copy[nb];
    printf("\nTesting bestfit\n");
    for (int i = 0; i < nr; i++) {
        copyFromTo(blocks, blocks_copy, nb);

        print("Before bestfit", blocks, nb);
        int x = best_fit(blocks, nb, req_array[i]);
        printf("%d bytes allocated from block %d by bestfit\n", req_array[i], x);
        print("After bestfit", blocks, nb);

        if (x == -1) {
            assertAllInRange(blocks_copy, nb, toNode(0), toNode(req_array[i]));
            assertAllEqual(blocks, blocks_copy, nb);
        } else {
            assert(x >= 0 && x < nb);
            assert(blocks_copy[x].size >= req_array[i]);
            assertNoneInRange(blocks_copy, nb, toNode(req_array[i]), toNode(blocks_copy[x].size));
            assertAllEqualBut(blocks, blocks_copy, nb, x);
            assert(blocks[x].size >= 0 && blocks[x].size + req_array[i] == blocks_copy[x].size);
        }
    }
}
void prop_worstfit(Node blocks[], int nb, const int req_array[], int nr) {
    Node blocks_copy[nb];
    printf("\nTesting worstfit\n");
    for (int i = 0; i < nr; i++) {
        copyFromTo(blocks, blocks_copy, nb);

        print("Before bestfit", blocks, nb);
        int x = worst_fit(blocks, nb, req_array[i]);
        printf("%d bytes allocated from block %d by worstfit\n", req_array[i], x);
        print("After worstfit", blocks, nb);

        if (x == -1) {
            assertAllInRange(blocks_copy, nb, toNode(0), toNode(req_array[i]));
            assertAllEqual(blocks, blocks_copy, nb);
        } else {
            assert(x >= 0 && x < nb);
            assert(blocks_copy[x].size >= req_array[i]);
            assertAllLTE(blocks_copy, nb, toNode(blocks_copy[x].size));
            assertAllEqualBut(blocks, blocks_copy, nb, x);
            assert(blocks[x].size >= 0 && blocks[x].size + req_array[i] == blocks_copy[x].size);
        }
    }
}

void test1() {
    Node blocks[] = {300, 600, 350, 200, 750, 125};
    int reqs[] = {115, 500, 358, 200, 375};
    int blocks_size = sizeof(blocks) / sizeof(blocks[0]);
    int reqs_size = sizeof(reqs) / sizeof(reqs[0]);

    prop_firstfit(blocks, blocks_size, reqs, reqs_size);
}

void test2() {
    for (int t = 0; t < 5; t++) {
        printf("Test2(%d)\n", t);
        int nblocks = 1 + rand() % 10;
        int nreqs = 1 + rand() % 10;

        Node *blocks = malloc(nblocks * sizeof(Node));
        int *reqs = malloc(nreqs * sizeof(int));

        int x = 0;
        for (int i = 0; i < nblocks; i++) {
            blocks[i].size = (rand() % 20) * 25;
        }
        for (int i = 0; i < nreqs; i++) {
            reqs[i] = (rand() % 20) * 25;
        }

        prop_firstfit(blocks, nblocks, reqs, nreqs);

        free(blocks);
        free(reqs);
    }
}

void test3() {
    for (int t = 0; t < 5; t++) {
        printf("Test3(%d)\n", t);
        int nblocks = 1 + rand() % 10;
        int nreqs = 1 + rand() % 10;

        Node *blocks = malloc(nblocks * sizeof(Node));
        int *reqs = malloc(nreqs * sizeof(int));

        int x = 0;
        for (int i = 0; i < nblocks; i++) {
            blocks[i].size = (rand() % 20) * 100;
        }
        for (int i = 0; i < nreqs; i++) {
            reqs[i] = (rand() % 20) * 50;
        }

        prop_bestfit(blocks, nblocks, reqs, nreqs);

        free(blocks);
        free(reqs);
    }
}

void test4() {
    Node blocks[] = {300, 600, 350, 200, 750, 125};
    int reqs[] = {115, 500, 358, 200, 375};
    int blocks_size = sizeof(blocks) / sizeof(blocks[0]);
    int reqs_size = sizeof(reqs) / sizeof(reqs[0]);

    prop_bestfit(blocks, blocks_size, reqs, reqs_size);
}

void test5() {
    for (int t = 0; t < 5; t++) {
        printf("Test5(%d)\n", t);
        int nblocks = 1 + rand() % 10;
        int nreqs = 1 + rand() % 10;

        Node *blocks = malloc(nblocks * sizeof(Node));
        int *reqs = malloc(nreqs * sizeof(int));

        int x = 0;
        for (int i = 0; i < nblocks; i++) {
            blocks[i].size = (rand() % 20) * 25;
        }
        for (int i = 0; i < nreqs; i++) {
            reqs[i] = (rand() % 20) * 25;
        }

        prop_bestfit(blocks, nblocks, reqs, nreqs);

        free(blocks);
        free(reqs);
    }
}

void test6() {
    for (int t = 0; t < 5; t++) {
        printf("Test6(%d)\n", t);
        int nblocks = 1 + rand() % 10;
        int nreqs = 1 + rand() % 10;

        Node *blocks = malloc(nblocks * sizeof(Node));
        int *reqs = malloc(nreqs * sizeof(int));

        int x = 0;
        for (int i = 0; i < nblocks; i++) {
            blocks[i].size = (rand() % 20) * 100;
        }
        for (int i = 0; i < nreqs; i++) {
            reqs[i] = (rand() % 20) * 50;
        }

        prop_worstfit(blocks, nblocks, reqs, nreqs);

        free(blocks);
        free(reqs);
    }
}

void test7() {
    Node blocks[] = {300, 600, 350, 200, 750, 125};
    int reqs[] = {115, 500, 358, 200, 375};
    int blocks_size = sizeof(blocks) / sizeof(blocks[0]);
    int reqs_size = sizeof(reqs) / sizeof(reqs[0]);

    prop_worstfit(blocks, blocks_size, reqs, reqs_size);
}

void test8() {
    for (int t = 0; t < 5; t++) {
        printf("Test8(%d)\n", t);
        int nblocks = 1 + rand() % 10;
        int nreqs = 1 + rand() % 10;

        Node *blocks = malloc(nblocks * sizeof(Node));
        int *reqs = malloc(nreqs * sizeof(int));

        int x = 0;
        for (int i = 0; i < nblocks; i++) {
            blocks[i].size = (rand() % 20) * 25;
        }
        for (int i = 0; i < nreqs; i++) {
            reqs[i] = (rand() % 20) * 25;
        }

        prop_worstfit(blocks, nblocks, reqs, nreqs);

        free(blocks);
        free(reqs);
    }
}

void test9() {
    for (int t = 0; t < 5; t++) {
        printf("Test9(%d)\n", t);
        int nblocks = 1 + rand() % 10;
        int nreqs = 1 + rand() % 10;

        Node *blocks = malloc(nblocks * sizeof(Node));
        int *reqs = malloc(nreqs * sizeof(int));

        int x = 0;
        for (int i = 0; i < nblocks; i++) {
            blocks[i].size = (rand() % 20) * 100;
        }
        for (int i = 0; i < nreqs; i++) {
            reqs[i] = (rand() % 20) * 50;
        }

        prop_worstfit(blocks, nblocks, reqs, nreqs);

        free(blocks);
        free(reqs);
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
    test9();
    printf("\n!! Congratulations, all tests passed !!\n");
    return 0;
}
