#include <stdio.h>

#define MAX 100

typedef struct {
    int value;
    int listIndex;
    int elementIndex;
} HeapNode;

typedef struct {
    HeapNode data[MAX];
    int size;
} MinHeap;

void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeap *heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->data[left].value < heap->data[smallest].value)
        smallest = left;

    if (right < heap->size && heap->data[right].value < heap->data[smallest].value)
        smallest = right;

    if (smallest != i) {
        swap(&heap->data[i], &heap->data[smallest]);
        heapify(heap, smallest);
    }
}

void insertHeap(MinHeap *heap, HeapNode node) {
    heap->data[heap->size++] = node;
    int i = heap->size - 1;

    while (i > 0 && heap->data[(i - 1) / 2].value > heap->data[i].value) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

HeapNode extractMin(MinHeap *heap) {
    HeapNode root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    heapify(heap, 0);
    return root;
}

void mergeKSortedLists(int lists[][MAX], int sizes[], int k) {
    MinHeap heap;
    heap.size = 0;

    for (int i = 0; i < k; i++) {
        if (sizes[i] > 0) {
            HeapNode node = {lists[i][0], i, 0};
            insertHeap(&heap, node);
        }
    }

    printf("\nMerged List: ");

    while (heap.size > 0) {
        HeapNode min = extractMin(&heap);
        printf("%d ", min.value);

        int nextIndex = min.elementIndex + 1;
        if (nextIndex < sizes[min.listIndex]) {
            HeapNode next = {lists[min.listIndex][nextIndex], min.listIndex, nextIndex};
            insertHeap(&heap, next);
        }
    }
    printf("\n");
}

int main() {
    int k;
    printf("Enter number of sorted lists: ");
    scanf("%d", &k);

    int lists[10][MAX], sizes[10];
    for (int i = 0; i < k; i++) {
        printf("\nEnter size of list %d: ", i + 1);
        scanf("%d", &sizes[i]);
        printf("Enter elements (sorted): ");
        for (int j = 0; j < sizes[i]; j++)
            scanf("%d", &lists[i][j]);
    }

    mergeKSortedLists(lists, sizes, k);
    return 0;
}
