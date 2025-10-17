#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *p, int *q) {
    int tmp = *p;
    *p = *q;
    *q = tmp;
}

void print(const char *name, int data[], int size) {
    printf("%s :\n", name);
    for (int i = 0; i < size; i++) {
        printf(" %d ", data[i]);
    }
    printf("\n");
}

//
// Input:
//  data[n-1] is empty
//  data[0..n-2] is sorted,
//  ie: data is of: <x <x <x <x =x =x >x >x  _
//
// NOTE:
//   it shifts the empty slot to: <x <x <x <x =x =x _ >x >x
//   and then writes x
//
// Output: Insert x into correct position and ensures the array is sorted
//  ie: data is of: <x <x <x <x =x =x =x >x >x
//  Ensures stable sort
//
void insert(int data[], int n, int x) {
    int i;
    // Start from the last element, which is empty
    // Shift prev to myself if prev >x. Repeat
    for (i = n - 1; i > 0 && data[i - 1] > x; i--) {
        data[i] = data[i - 1];
    }
    // Finally write myself
    data[i] = x;
}

void insertionSort(int data[], int size) {
    for (int i = 1; i < size; i++) {
        int x = data[i];
        insert(data, i + 1, x);
    }
}

// expects array to have at least one element
// begin is inclusive, end is exclusive
//
// Output: returns the index of minimum element
int findMin(int data[], int begin, int end) {
    int minIndex = begin;
    for (int i = begin + 1; i < end; i++) {
        if (data[i] < data[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

void selectionSort(int data[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = findMin(data, i, size);
        if (i != minIndex) {
            swap(&data[i], &data[minIndex]);
        }
    }
}

int partition(int data[], int begin, int end) {

    // choose middle element as the pivot
    // and keep the pivot at the end
    swap(&data[(begin + end) / 2], &data[end]);

    int pivot = data[end];

    int p = begin;
    for (int i = begin; i < end; i++) {
        if (data[i] <= pivot) {
            swap(&data[p], &data[i]);
            p++;
        }
    }
    swap(&data[p], &data[end]);

    return p;
}

// [begin,end]: begin and end are inclusive
void quickSort(int data[], int begin, int end) {

    // handle error cases and base condition
    if (begin < 0 || end < 0 || begin > end || begin == end) {
        return;
    }

    int p = partition(data, begin, end);
    quickSort(data, begin, p - 1);
    quickSort(data, p + 1, end);
}

// Merge two sorted arrays into another sorted array
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

// Merge two sorted arrays into same sorted array
// Uses a tmp array of same length
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

// Let's say p is 100,
// we need to find the digit in the 100th place
//
// key(1234567, 100) is 5
//
int key(int x, int p) { return (x / p) % 10; }

void countingSort(int data[], int size, int tmp[], int p) {

    const int max = 9;
    // Step 1: Array with size max+1
    int count[max + 1]; // why? 0..9 digits only

    // Step 2: Find the count
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < size; i++) {
        count[key(data[i], p)]++;
    }

    // Step 3: Find the inclusive prefix sum
    for (int i = 1; i <= max; i++) {
        count[i] = count[i - 1] + count[i];
    }

    // Step 4: Write to appropriate location
    for (int i = size - 1; i >= 0; i--) {
        count[key(data[i], p)]--;
        tmp[count[key(data[i], p)]] = data[i];
    }

    // Step 5: write back
    for (int i = 0; i < size; i++) {
        data[i] = tmp[i];
    }
}

void radixSort(int data[], int size, int tmp[]) {

    // Step 1: Find max
    int max = data[0];
    for (int i = 1; i < size; i++) {
        if (max < data[i]) {
            max = data[i];
        }
    }

    // Step 2: Do stable sort from LSD to MSD
    for (int p = 1; p <= max; p = p * 10) {
        countingSort(data, size, tmp, p);
    }
}

int main() {
    int data[100];
    int size = 0;
    int tmp[100];

    // int xxx[]={3,1,4,1,5,9,2,6,5,3,5,8,9};
    int xxx[] = {312, 121, 441, 112, 513, 913, 265, 653, 523, 364, 531, 856, 913};
    size = sizeof(xxx) / sizeof(xxx[0]);

    for (int i = 0; i < size; i++) {
        data[i] = xxx[i];
    }
    print("input", data, size);
    // insertionSort(data,size);
    // selectionSort(data,size);
    // quickSort(data,0, size-1);
    mergeSort(data, 0, size - 1, tmp);
    // radixSort(data,size, tmp);
    print("output", data, size);

    // Print number of comparisons
    // Print number of writes

    return 0;
}
