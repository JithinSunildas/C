#include <asm-generic/errno.h>
#include <stdio.h>

int count;

void swap(int *p, int *q) {
    int tmp = *p;
    *p = *q;
    *q = tmp;
}

void copy(int cpyarr[], int arr[], int size) {
    for (int i = 0; i < size; i++)
        cpyarr[i] = arr[i];
}

void print(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n\n");
}

// Insertion sort
void insert(int arr[], int i) {
    int tmp = arr[i];
    for (i; i > 0 && arr[i - 1] > tmp; i--)
        arr[i] = arr[i - 1];
    arr[i] = tmp;
}
void insertion_sort(int data[], int size) {
    for (int i = 1; i < size; i++) {
        insert(data, i);
    }
}

// Selection sort
int find_min(int i, int arr[], int size) {
    int min = i;
    for (int j = i; j < size; j++) {
        if (arr[j] < arr[min])
            min = j;
    }
    return min;
}
void selection_sort(int data[], int size) {
    int min_index;
    for (int i = 0; i < size; i++) {
        min_index = find_min(i, data, size);
        if (i != min_index)
            swap(&data[i], &data[min_index]);
    }
}

// Quick sort
int partition(int arr[], int begin, int end) {
    swap(&arr[(begin + end) / 2], &arr[end]);
    int pos = begin;

    for (int i = begin; i < end; i++) {
        if (arr[i] <= arr[end]) {
            swap(&arr[i], &arr[pos]);
            pos++;
        }
    }
    swap(&arr[end], &arr[pos]);
    return pos;
}
void quick_sort(int data[], int begin, int end) {
    // begin == end is base case and others are exceptions and error cases.
    if (begin >= end) {
        return;
    }

    int p = partition(data, begin, end);
    quick_sort(data, begin, p - 1);
    quick_sort(data, p + 1, end);
}

// Merge sort
void merge(int data[], int size, int begin, int mid, int end) {
    int len1 = mid - begin + 1;
    int len2 = end - mid;
    int arr1[len1], arr2[len2];
    for (int i = 0; i < len1; i++) {
        arr1[i] = data[i];
    }
    for (int i = 0; i < len2; i++) {
        arr1[i] = data[mid + i];
    }
}
void mergeSort(int data[], int begin, int mid, int end) {
    if (begin >= end)
        return;
    int mid = (begin + end) / 2;
    mergeSort(data, begin, mid);
    mergeSort(data, mid + 1, end);
    merge(data, begin, mid, end);
}

int main() {
    int data[] = {5, 6, 1, 3, 7, 2, 5, 1, 2};
    int size = sizeof(data) / sizeof(int);
    printf("Data: \n");
    print(data, size);
    int insertionsort[size], selectionsort[size], quicksort[size];

    // Insertion sort
    copy(insertionsort, data, size);
    insertion_sort(insertionsort, size);
    printf("Insertion sort: \n");
    print(insertionsort, size);

    // Selection sort
    copy(selectionsort, data, size);
    selection_sort(selectionsort, size);
    printf("Selection sort: \n");
    print(selectionsort, size);

    // Quick sort
    copy(quicksort, data, size);
    quick_sort(quicksort, 0, size - 1);
    printf("Quick sort: \n");
    print(quicksort, size);

    return 0;
}
