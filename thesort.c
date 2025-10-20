#include <stdio.h>
int steps = 0;
void swap(int *p, int *q) {
    int temp = *p;
    *p = *q;
    *q = temp;
}
void print(int data[], int size) {
    for (int i = 0; i < size; i++) {
        printf("  %d", data[i]);
    }
}
void insert(int data[], int n, int x) {
    steps += 2;
    int i;
    for (i = n - 1; i > 0 && data[i - 1] > x; i--) {
        steps += 2;
        data[i] = data[i - 1];
        steps++;
    }
    steps += 1;
    data[i] = x;
    steps = steps + 1;
}
void insertionsort(int data[], int size) {
    steps += 2;
    for (int i = 1; i < size; i++) {
        steps += 2;
        int x = data[i];
        insert(data, i + 1, x);
        steps++;
    }
}
int findmin(int data[], int begin, int end) {
    steps += 3;
    int minindex = begin;
    for (int i = begin + 1; i < end; i++) {
        steps += 1;
        if (data[i] < data[minindex]) {
            steps += 2;
            minindex = i;
            steps += 1;
        }
    }
    return minindex;
}
void selectionsort(int data[], int size) {
    steps += 2;
    for (int i = 0; i < size - 1; i++) {
        steps += 2;
        int minindex = findmin(data, i, size);
        if (i != minindex) {
            steps += 3;
            swap(&data[i], &data[minindex]);
        }
    }
}
int partition(int data[], int begin, int end) {
    steps += 3;
    swap(&data[(begin + end) / 2], &data[end]);
    steps += 3;
    int pivot = data[end];
    int p = begin;
    for (int i = begin; i < end; i++) {
        steps += 2;
        if (data[i] < pivot) {
            steps += 1;
            swap(&data[p], &data[i]);
            steps += 3;
            p++;
            steps += 1;
        }
    }
    swap(&data[p], &data[end]);
    steps += 3;
    return p;
}
void quicksort(int data[], int begin, int end) {
    steps += 3;
    if (begin < 0 || end < 0 || begin > end || begin == end) {
        steps += 4;
        return;
    }
    int p;
    p = partition(data, begin, end);
    steps += 1;
    quicksort(data, begin, p - 1);
    quicksort(data, p + 1, end);
    steps += 2;
}
void merge2(const int data[], int begin, int mid, int end, int out[]) {
    steps += 3;
    int ia, ib, ic;
    for (ia = begin, ib = mid + 1, ic = begin; ia <= mid && ib <= end; ic++) {
        steps += 3;
        if (data[ia] <= data[ib]) {
            steps += 2;
            out[ic] = data[ia];
            ia++;
            steps += 1;
        } else {
            out[ic] = data[ib];
            ib++;
            steps += 1;
        }
    }
    for (; ia <= mid; ic++) {
        steps += 2;
        out[ic] = data[ia];
        ia++;
        steps += 1;
    }
    for (; ib <= end; ic++) {
        steps += 2;
        out[ic] = data[ib];
        ib++;
        steps += 1;
    }
}
void merge(int data[], int begin, int mid, int end, int tmp[]) {
    steps += 2;
    for (int i = begin; i <= end; i++) {
        steps += 2;
        tmp[i] = data[i];
    }
    steps += 1;
    merge2(tmp, begin, mid, end, data);
    steps += 1;
}

void mergeSort(int data[], int begin, int end, int tmp[]) {
    int mid = (begin + end) / 2;
    steps += 2;

    if (begin > end || begin == end) {
        steps += 2;
        return;
    }

    mergeSort(data, begin, mid, tmp);
    mergeSort(data, mid + 1, end, tmp);
    merge(data, begin, mid, end, tmp);
    steps += 3;
}

int key(int x, int p) { return (x / p) % 10; }
void countingSort(int data[], int size, int tmp[], int p) {
    steps += 2;
    const int max = 9;
    int count[max + 1], i;
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
        steps += 2;
    }
    for (int i = 0; i < size; i++) {
        count[key(data[i], p)]++;
        steps += 3;
    }
    for (int i = 1; i <= max; i++) {
        steps += 3;
        count[i] = count[i - 1] + count[i];
    }
    steps += 1;
    for (int i = size - 1; i >= 0; i--) {
        steps += 3;
        count[key(data[i], p)]--;
        tmp[count[key(data[i], p)]] = data[i];
    }
    steps += 1;
    for (int i = 0; i < size; i++) {
        steps += 2;
        data[i] = tmp[i];
    }
    steps += 1;
}
void radixsort(int data[], int size, int tmp[]) {
    steps += 2;
    int max = data[0];
    for (int i = 1; i < size; i++) {
        steps += 2;
        if (max < data[i]) {
            max = data[i];
            steps += 1;
        }
    }
    steps += 1;
    for (int p = 1; p <= max; p = p * 10) {
        steps += 2;
        countingSort(data, size, tmp, p);
        steps += 1;
    }
}

int main() {
    int data[100];
    int tmp[100];
    int size = 0;

    int original[] = {233, 123, 567, 313, 660};
    size = sizeof(original) / sizeof(original[0]);

    printf("INPUT:\n");
    print(original, size);
    printf("\n");

    for (int i = 0; i < size; i++)
        data[i] = original[i];
    steps = 0;
    insertionsort(data, size);
    printf("\nInsertion Sort:\n");
    print(data, size);
    printf("\nTotal Steps = %d\n", steps);

    for (int i = 0; i < size; i++)
        data[i] = original[i];
    steps = 0;
    selectionsort(data, size);
    printf("\nSelection Sort:\n");
    print(data, size);
    printf("\nTotal Steps = %d\n", steps);

    for (int i = 0; i < size; i++)
        data[i] = original[i];
    steps = 0;
    quicksort(data, 0, size - 1);
    printf("\nQuick Sort:\n");
    print(data, size);
    printf("\nTotal Steps = %d\n", steps);

    for (int i = 0; i < size; i++)
        data[i] = original[i];
    steps = 0;
    mergeSort(data, 0, size - 1, tmp);
    printf("\nMerge Sort:\n");
    print(data, size);
    printf("\nTotal Steps = %d\n", steps);

    for (int i = 0; i < size; i++)
        data[i] = original[i];
    steps = 0;
    radixsort(data, size, tmp);
    printf("\nRadix Sort:\n");
    print(data, size);
    printf("\nTotal Steps = %d\n", steps);

    return 0;
}
