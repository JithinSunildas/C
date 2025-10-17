#include <stdio.h>

int main() {
    int arr[] = {0, 0, 0, 0};

    int i, j, k, size;
    size = 4;
    for (i = 0; i < size; i++) {
        k = j;
        for (j = i + 1; j < size; j++) {
            for (k = j; k >= 0; k--)
                if (arr[i] == arr[j])
                    printf("%d", arr[i]);
        }
    }
    printf("\n");
    return 0;
}
