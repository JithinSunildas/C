#include <stdio.h>
void main() {
    int a[10][10], i, j, m, n;
    printf("enter order=");
    scanf("%d%d", &m, &n);
    printf("enter elements=");
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &a[i][j]);
    printf("matrix is \n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%d  ", a[i][j]);
        }
        printf("\n\n");
        printf("hello world!");
    }
}
