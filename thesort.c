#include <stdio.h>

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
    int i;
    for (i = n - 1; i > 0 && data[i - 1] > x; i--) {
        data[i] = data[i - 1];
    }
    data[i] = x;
}

void insertionsort(int data[], int size) {
    for (int i = 1; i < size; i++) {
        int x = data[i];
        insert(data, i + 1, x);
    }
}

int findmin(int data[], int begin, int end) {
    int minindex = begin;
    for (int i = begin + 1; i < end; i++) {
        if (data[i] < data[minindex]) {
            minindex = i;
        }
    }
    return minindex;
}

void selectionsort(int data[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minindex = findmin(data, i, size);
        if (i != minindex) {
            swap(&data[i], &data[minindex]);
        }
    }
}

int partition(int data[], int begin, int end) {
    swap(&data[(begin + end) / 2], &data[end]);
    int pivot = data[end];
    int p = begin;
    for (int i = begin; i < end; i++) {
        if (data[i] < pivot) {
            swap(&data[p], &data[i]);
            p++;
        }
    }
    swap(&data[p], &data[end]);
    return p;
}

void quicksort(int data[], int begin, int end) {
    if (begin < 0 || end < 0 || begin > end || begin == end) {
        return;
    }
    int p;
    p = partition(data, begin, end);
    quicksort(data, begin, p - 1);
    quicksort(data, p + 1, end);
}

void merge2(const int data[], int begin, int mid, int end, int out[]) {
    int ia, ib, ic;
    for (ia = begin, ib = mid + 1, ic = begin; ia <= mid && ib <= end; ic++) {
        if (data[ia] <= data[ib]) {
            out[ic] = data[ia];
            ia++;
        } else {
            out[ic] = data[ib];
            ib++;
        }
    }
    for (; ia <= mid; ic++) {
        out[ic] = data[ia];
        ia++;
    }
    for (; ib <= end; ic++) {
        out[ic] = data[ib];
        ib++;
    }
}

void merge(int data[], int begin, int mid, int end, int tmp[]) {
    for (int i = begin; i <= end; i++) {
        tmp[i] = data[i];
    }
    merge2(tmp, begin, mid, end, data);
}

void mergeSort(int data[], int begin, int end, int tmp[]) {
    int mid = (begin + end) / 2;

    if (begin > end || begin == end) {
        return;
    }

    mergeSort(data, begin, mid, tmp);
    mergeSort(data, mid + 1, end, tmp);
    merge(data, begin, mid, end, tmp);
}

int key(int x, int p) { return (x / p) % 10; }

void countingSort(int data[], int size, int tmp[], int p) {
    const int max = 9;
    int count[max + 1], i;
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        count[key(data[i], p)]++;
    }
    for (int i = 1; i <= max; i++) {
        count[i] = count[i - 1] + count[i];
    }
    for (int i = size - 1; i >= 0; i--) {
        count[key(data[i], p)]--;
        tmp[count[key(data[i], p)]] = data[i];
    }
    for (int i = 0; i < size; i++) {
        data[i] = tmp[i];
    }
}

void radixsort(int data[], int size, int tmp[]) {
    int max = data[0];
    for (int i = 1; i < size; i++) {
        if (max < data[i]) {
            max = data[i];
        }
    }
    for (int p = 1; p <= max; p = p * 10) {
        countingSort(data, size, tmp, p);
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
    insertionsort(data, size);
    printf("\nInsertion Sort:\n");
    print(data, size);

    for (int i = 0; i < size; i++)
        data[i] = original[i];
    selectionsort(data, size);
    printf("\nSelection Sort:\n");
    print(data, size);

    for (int i = 0; i < size; i++)
        data[i] = original[i];
    quicksort(data, 0, size - 1);
    printf("\nQuick Sort:\n");
    print(data, size);

    for (int i = 0; i < size; i++)
        data[i] = original[i];
    mergeSort(data, 0, size - 1, tmp);
    printf("\nMerge Sort:\n");
    print(data, size);

    for (int i = 0; i < size; i++)
        data[i] = original[i];
    radixsort(data, size, tmp);
    printf("\nRadix Sort:\n");
    print(data, size);

    return 0;
}
